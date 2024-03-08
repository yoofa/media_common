/*
 * media_packet.cc
 * Copyright (C) 2023 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#include "media_packet.h"
#include "base/checks.h"

namespace ave {

MediaPacket MediaPacket::Create(size_t size) {
  return MediaPacket(size, protect_parameter());
}

MediaPacket MediaPacket::CreateWithHandle(void* handle) {
  return MediaPacket(handle, protect_parameter());
}

MediaPacket::MediaPacket(size_t size, protect_parameter)
    : size_(size),
      data_(std::make_shared<base::Buffer8>(size)),
      native_handle_(nullptr),
      buffer_type_(PacketBufferType::kTypeNormal),
      media_type_(MediaType::UNKNOWN),
      sample_info_(0) {}

MediaPacket::MediaPacket(void* handle, protect_parameter)
    : size_(0),
      data_(nullptr),
      native_handle_(handle),
      buffer_type_(PacketBufferType::kTypeNativeHandle),
      media_type_(MediaType::UNKNOWN),
      sample_info_(0) {}

MediaPacket::~MediaPacket() {}

MediaPacket::MediaPacket(const MediaPacket& other) {
  if (other.buffer_type_ == PacketBufferType::kTypeNormal) {
    data_ = other.data_;
    native_handle_ = nullptr;
    buffer_type_ = PacketBufferType::kTypeNormal;
  } else {
    data_ = nullptr;
    native_handle_ = other.native_handle_;
    buffer_type_ = PacketBufferType::kTypeNativeHandle;
  }

  size_ = other.size_;
  media_type_ = other.media_type_;
  sample_info_ = other.sample_info_;
}

void MediaPacket::SetMediaType(MediaType type) {
  if (media_type_ != type) {
    media_type_ = type;
    switch (media_type_) {
      case MediaType::AUDIO:
        sample_info_ = AudioSampleInfo();
        break;
      case MediaType::VIDEO:
        sample_info_ = VideoSampleInfo();
        break;
      default:
        break;
    }
  }
}

void MediaPacket::SetSize(size_t size) {
  AVE_DCHECK(buffer_type_ == PacketBufferType::kTypeNormal);
  AVE_DCHECK(size > 0);
  data_->SetSize(size);
  size_ = data_->size();
}

void MediaPacket::SetData(uint8_t* data, size_t size) {
  AVE_DCHECK(buffer_type_ == PacketBufferType::kTypeNormal);
  data_->SetData(data, size);
  size_ = data_->size();
}

AudioSampleInfo* MediaPacket::audio_info() {
  return std::get_if<AudioSampleInfo>(&sample_info_);
}

VideoSampleInfo* MediaPacket::video_info() {
  return std::get_if<VideoSampleInfo>(&sample_info_);
}

uint8_t* MediaPacket::data() {
  if (buffer_type_ == PacketBufferType::kTypeNormal) {
    return data_->data();
  } else {
    return nullptr;
  }
}

}  // namespace ave
