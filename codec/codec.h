/*
 * codec.h
 * Copyright (C) 2024 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#ifndef CODEC_H
#define CODEC_H

#include <memory>

#include "base/errors.h"

#include "../crypto/crypto.h"
#include "../foundation/media_utils.h"
#include "../foundation/message.h"
#include "../video/video_render.h"

#include "codec_buffer.h"

namespace ave {
namespace media {

struct CodecInfo {
  std::string name;
  std::string mime;
  MediaType media_type;
  bool is_encoder;
  bool hardware_accelerated;
};

// callback for codec
class CodecCallback {
  virtual ~CodecCallback() = default;
  // fill the input buffer
  virtual void OnInputBufferAvailable(int32_t index) = 0;
  // output buffer is available
  virtual void OnOutputBufferAvailable(int32_t index) = 0;
  // output format is changed
  virtual void OnOutputFormatChanged(
      const std::shared_ptr<Message>& format) = 0;
  // error happened
  virtual void OnError(status_t error) = 0;
  // frame is rendered
  virtual void OnFrameRendered(std::shared_ptr<Message> notify) = 0;
};

// codec configuration
struct CodecConfig {
  CodecInfo info;
  std::shared_ptr<VideoRender> video_render;
  std::shared_ptr<Crypto> crypto;
  std::shared_ptr<Message> format;
};

// this class is porting from Android MediaCodec
class Codec {
  virtual ~Codec() = default;

  // video_render: decoder -> video render path
  virtual status_t Configure(const std::shared_ptr<CodecConfig()>& config) = 0;

  virtual status_t SetCallback(std::shared_ptr<CodecCallback> callback) = 0;

  // running operation
  virtual status_t Start() = 0;
  virtual status_t Stop() = 0;
  virtual status_t Reset() = 0;
  virtual status_t Flush() = 0;
  virtual status_t Release() = 0;

  virtual status_t DequeueInputBuffer(int32_t index, int64_t timeout_ms) = 0;

  /* queueInputBuffer to codec, will copy the data to codec internal buffer
   * return -EAGAIN if the codec is not ready or input queue in full
   */
  virtual status_t QueueInputBuffer(std::shared_ptr<CodecBuffer>& buffer,
                                    int64_t timeout_ms) = 0;

  virtual status_t DequeueOutputBuffer(std::shared_ptr<CodecBuffer>& buffer,
                                       int64_t timeout_ms) = 0;

  /* release the output buffer
   * render: true - render the buffer, false - only release the buffer
   */
  virtual status_t ReleaseOutputBuffer(
      std::shared_ptr<CodecBuffer>& buffer,
      bool render) = 0;
};

}  // namespace media
}  // namespace ave

#endif /* !CODEC_H */
