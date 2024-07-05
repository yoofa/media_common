/*
 * buffer.h
 * Copyright (C) 2022 youfa.song <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#ifndef BUFFER_H
#define BUFFER_H

#include <memory>

#include "base/constructor_magic.h"

#include "message.h"

namespace ave {
namespace media {

class Buffer {
 public:
  Buffer(size_t capacity);
  Buffer(void* data, size_t capacity);

  uint8_t* base() { return (uint8_t*)data_; }
  uint8_t* data() { return (uint8_t*)data_ + range_offset_; }
  size_t capacity() const { return capacity_; }
  size_t size() const { return range_length_; }
  size_t offset() const { return range_offset_; }
  void setRange(size_t offset, size_t size);

  // create buffer from dup of some memory block
  static std::shared_ptr<Buffer> CreateAsCopy(const void* data,
                                              size_t capacity);
  void setInt32Data(int32_t data) { int32_data_ = data; }
  int32_t int32Data() const { return int32_data_; }
  std::shared_ptr<Message> meta();

  virtual ~Buffer();

 private:
  std::shared_ptr<Message> meta_;
  void* data_;
  size_t capacity_;
  size_t range_offset_;
  size_t range_length_;
  int32_t int32_data_;
  bool owns_data_;

  AVE_DISALLOW_COPY_AND_ASSIGN(Buffer);
};

}  // namespace media
} /* namespace ave */

#endif /* !BUFFER_H */
