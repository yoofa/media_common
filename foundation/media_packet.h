/*
 * media_packet.h
 * Copyright (C) 2023 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#ifndef MEDIA_PACKET_H
#define MEDIA_PACKET_H

#include <memory>
#include <variant>

#include "base/buffer.h"

#include "media_utils.h"

namespace ave {
namespace media {

class MediaPacket {
 protected:
  // for private construct
  struct protect_parameter {
    explicit protect_parameter() = default;
  };

 public:
  enum class PacketBufferType {
    kTypeNormal,
    kTypeNativeHandle,
  };

  static MediaPacket Create(size_t size);
  static MediaPacket CreateWithHandle(void* handle);

 private:
  explicit MediaPacket(size_t size, protect_parameter);
  MediaPacket(void* handle, protect_parameter);

 public:
  ~MediaPacket();
  // only support copy construct
  MediaPacket(const MediaPacket& other);

  void SetMediaType(MediaType type);
  void SetSize(size_t size);
  void SetData(uint8_t* data, size_t size);

  // get sample info
  // TODO(youfa) complete other MediaType info when merge avelayer
  AudioSampleInfo* audio_info();
  VideoSampleInfo* video_info();

  size_t size() const { return size_; }
  std::shared_ptr<base::Buffer8>& buffer() { return data_; }
  uint8_t* data();

  MediaType media_type() const { return media_type_; }
  PacketBufferType buffer_type() const { return buffer_type_; }
  void* native_handle() const { return native_handle_; }

 private:
  using SampleInfo = std::variant<int, AudioSampleInfo, VideoSampleInfo>;

  size_t size_;
  std::shared_ptr<base::Buffer8> data_;
  void* native_handle_;
  PacketBufferType buffer_type_;
  MediaType media_type_;

  // audio or video or data sample info
  SampleInfo sample_info_;
};

}  // namespace media
}  // namespace ave

#endif /* !MEDIA_PACKET_H */
