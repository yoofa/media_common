/*
 * buffer.cc
 * Copyright (C) 2022 youfa.song <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#include "buffer.h"

#include <cstring>
#include <memory>

#include "base/checks.h"

namespace ave {
namespace media {

Buffer::Buffer(size_t capacity)
    : data_(malloc(capacity)),
      capacity_(capacity),
      range_offset_(0),
      range_length_(capacity),
      int32_data_(0),
      owns_data_(true) {}

Buffer::Buffer(void* data, size_t capacity)
    : data_(data),
      capacity_(capacity),
      range_offset_(0),
      range_length_(capacity),
      int32_data_(0),
      owns_data_(false) {}

// static
std::shared_ptr<Buffer> Buffer::CreateAsCopy(const void* data,
                                             size_t capacity) {
  std::shared_ptr<Buffer> res(std::make_shared<Buffer>(capacity));
  memcpy(res->data(), data, capacity);
  return res;
}

Buffer::~Buffer() {
  if (owns_data_) {
    if (data_ != NULL) {
      free(data_);
      data_ = NULL;
    }
  }
}

void Buffer::setRange(size_t offset, size_t size) {
  AVE_CHECK_LE(offset, capacity_);
  AVE_CHECK_LE(offset + size, capacity_);

  range_offset_ = offset;
  range_length_ = size;
}

std::shared_ptr<Message> Buffer::meta() {
  if (meta_.get() == nullptr) {
    meta_ = std::make_shared<Message>();
  }
  return meta_;
}

}  // namespace media
} /* namespace ave */
