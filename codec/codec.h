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

class CodecCallback {
  virtual ~CodecCallback() = default;
  virtual void onInputBufferAvailable(int32_t index) = 0;
  virtual void onOutputBufferAvailable(int32_t index) = 0;
  virtual void onOutputFormatChanged(
      const std::shared_ptr<Message>& format) = 0;
  virtual void onError(status_t error) = 0;
  virtual void onFrameRendered(std::shared_ptr<Message> notify) = 0;
};

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
  virtual status_t configure(const std::shared_ptr<CodecConfig()>& config) = 0;

  virtual status_t setCallback(std::shared_ptr<CodecCallback> callback) = 0;

  // running operation
  virtual status_t start() = 0;
  virtual status_t stop() = 0;
  virtual status_t reset() = 0;
  virtual status_t flush() = 0;
  virtual status_t release() = 0;

  /* queueInputBuffer to codec, will copy the data to codec internal buffer
   * return -EAGAIN if the codec is not ready or input queue in full
   */
  virtual status_t queueInputBuffer(std::shared_ptr<CodecBuffer>& buffer,
                                    int64_t timeout) = 0;

  virtual status_t dequeueOutputBuffer(std::shared_ptr<CodecBuffer>& buffer,
                                       int64_t timeout) = 0;

  virtual status_t renderAndReleaseOutputBuffer(
      std::shared_ptr<CodecBuffer>& buffer,
      bool render) = 0;
};

}  // namespace media
}  // namespace ave

#endif /* !CODEC_H */
