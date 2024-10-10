/*
 * video_sink.h
 * Copyright (C) 2022 youfa.song <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#ifndef VIDEO_SINK_H
#define VIDEO_SINK_H

#include <memory>

#include "media/foundation/message_object.h"

namespace ave {
namespace media {

class VideoSink : public MessageObject {
 public:
  VideoSink() = default;
  ~VideoSink() override = default;
  virtual void onFrame() = 0;
  virtual int64_t render_latency() { return 0; }
};

}  // namespace media
}  // namespace ave

#endif /* !VIDEO_SINK_H */
