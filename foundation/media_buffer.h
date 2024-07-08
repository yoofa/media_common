/*
 * media_buffer.h
 * Copyright (C) 2021 youfa.song <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#ifndef AVE_MEDIA_BUFFER_H
#define AVE_MEDIA_BUFFER_H

#include "base/buffer.h"
#include "message.h"

namespace ave {
namespace media {

class MediaBuffer {
 public:
  MediaBuffer(std::shared_ptr<base::Buffer> buffer,
              std::shared_ptr<Message> meta);
  virtual ~MediaBuffer() = default;

  uint8_t* base();
  uint8_t* data();
  size_t capacity() const;
  size_t size() const;
  size_t offset() const;
  std::shared_ptr<Message> meta();

  void setRange(size_t offset, size_t size);
  void setMeta(std::shared_ptr<Message> meta);

 private:
  std::shared_ptr<Message> meta_;
  std::shared_ptr<base::Buffer> buffer_;
};

}  // namespace media
}  // namespace ave

#endif /* !AVE_MEDIA_BUFFER_H */
