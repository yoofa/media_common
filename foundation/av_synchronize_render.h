/*
 * av_synchronize_render.h
 * Copyright (C) 2024 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#ifndef AV_SYNCHRONIZE_RENDER_H
#define AV_SYNCHRONIZE_RENDER_H

#include <functional>
#include <list>

#include "base/task_util/task_runner.h"
#include "media/audio/audio_track.h"
#include "media_buffer.h"
#include "media_clock.h"
#include "media_utils.h"

namespace ave {
namespace media {

class AVSynchronizeRender : public MessageObject {
 public:
  AVSynchronizeRender();
  ~AVSynchronizeRender() override;

  void QueueBuffer(MediaType stream_type,
                   std::shared_ptr<MediaBuffer> buffer,
                   std::function<void()> comsume_notify = nullptr);

  void Flush();

  void Pause();
  void Resume();

  void SetVideoFrameRate(float fps);

  void SetAudioTrack(std::shared_ptr<AudioTrack> audio_track);

 private:
  struct QueueEntry {
    MediaType stream_type;
    std::shared_ptr<MediaBuffer> buffer;
    std::function<void()> consumed_notify;
    std::shared_ptr<Message> meta;
  };

  std::unique_ptr<base::TaskRunner> sync_runner_;
  std::shared_ptr<AudioTrack> audio_track_;

  std::list<QueueEntry> audio_queue_;
  std::list<QueueEntry> video_queue_;

  std::shared_ptr<MediaClock> media_clock_;

  bool use_audio_callback_;
};

}  // namespace media
}  // namespace ave

#endif /* !AV_SYNCHRONIZE_RENDER_H */
