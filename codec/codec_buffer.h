/*
 * codec_buffer.h
 * Copyright (C) 2024 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#ifndef CODEC_BUFFER_H
#define CODEC_BUFFER_H

#include "../foundation/buffer.h"

namespace ave {
namespace media {

class CodecBuffer : public Buffer {
 public:
  CodecBuffer(size_t capacity);
  ~CodecBuffer() override;

 private:
};

}  // namespace media
}  // namespace ave

#endif /* !CODEC_BUFFER_H */
