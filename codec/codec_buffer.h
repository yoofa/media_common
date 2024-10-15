/*
 * codec_buffer.h
 * Copyright (C) 2024 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#ifndef CODEC_BUFFER_H
#define CODEC_BUFFER_H

#include "../foundation/buffer.h"
#include "../foundation/media_format.h"

namespace ave {
namespace media {

class CodecBuffer : public Buffer {
 public:
  CodecBuffer(size_t capacity);
  ~CodecBuffer() override;

  int32_t index() const { return buffer_index_; }

  int32_t texture_id() const { return texture_id_; }

  void* native_handle() const { return native_handle_; }

 private:
  int32_t buffer_index_;
  int32_t texture_id_;
  void* native_handle_;
  std::shared_ptr<MediaFormat> format_;
};

}  // namespace media
}  // namespace ave

#endif /* !CODEC_BUFFER_H */
