/*
 * codec_buffer.cc
 * Copyright (C) 2024 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#include "codec_buffer.h"

namespace ave {

namespace media {

CodecBuffer::CodecBuffer() : CodecBuffer(0) {}

CodecBuffer::CodecBuffer(size_t capacity)
    : Buffer(capacity),
      buffer_index_(-1),
      texture_id_(-1),
      native_handle_(nullptr),
      buffer_type_(BufferType::kTypeNormal),
      format_(std::make_shared<MediaFormat>()) {}

CodecBuffer::~CodecBuffer() = default;

}  // namespace media

}  // namespace ave
