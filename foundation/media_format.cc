/*
 * media_format.cc
 * Copyright (C) 2024 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#include "media_format.h"

#include "base/logging.h"

#include "media_utils.h"

namespace ave {
namespace media {

MediaFormat::MediaFormat()
    : stream_type_(MediaType::UNKNOWN),
      track_info_(MediaTrackInfo(stream_type_)) {}

MediaFormat& MediaFormat::SetStreamType(const MediaType stream_type) {
  if (stream_type_ != stream_type) {
    AVE_LOG(LS_WARNING) << "SetStreamType failed, stream type already set";
  }
  return *this;
}

MediaType MediaFormat::stream_type() const {
  return stream_type_;
}

MediaFormat& MediaFormat::SetMime(const char* mime) {
  if (!mime) {
    AVE_LOG(LS_WARNING) << "SetMime failed, mime is null";
  } else {
    mime_ = mime;
  }
  return *this;
}

std::string MediaFormat::mime() const {
  return mime_;
}

MediaFormat& MediaFormat::SetCodec(const CodecId codec) {
  switch (stream_type_) {
    case MediaType::VIDEO: {
      track_info_.video().codec_id = codec;
      break;
    }
    case MediaType::AUDIO: {
      track_info_.audio().codec_id = codec;
      break;
    }
    default: {
      break;
    }
  }
  return *this;
}

CodecId MediaFormat::codec() const {
  switch (stream_type_) {
    case MediaType::VIDEO: {
      return track_info_.video().codec_id;
    }
    case MediaType::AUDIO: {
      return track_info_.audio().codec_id;
    }
    default: {
      return CodecId::AVE_CODEC_ID_NONE;
    }
  }
}

MediaFormat& MediaFormat::SetBitrate(const int64_t bps) {
  switch (stream_type_) {
    case MediaType::VIDEO: {
      track_info_.video().bitrate_bps = bps;
      break;
    }
    case MediaType::AUDIO: {
      track_info_.audio().bitrate_bps = bps;
      break;
    }
    default: {
      break;
    }
  }
  return *this;
}

int64_t MediaFormat::bitrate() const {
  switch (stream_type_) {
    case MediaType::VIDEO: {
      return track_info_.video().bitrate_bps;
    }
    case MediaType::AUDIO: {
      return track_info_.audio().bitrate_bps;
    }
    default: {
      return -1;
    }
  }
}

MediaFormat& MediaFormat::SetDuration(const base::TimeDelta duration) {
  switch (stream_type_) {
    case MediaType::VIDEO: {
      track_info_.video().duration = duration;
      break;
    }
    case MediaType::AUDIO: {
      track_info_.audio().duration = duration;
      break;
    }
    default: {
      break;
    }
  }
  return *this;
}

base::TimeDelta MediaFormat::duration() const {
  switch (stream_type_) {
    case MediaType::VIDEO: {
      return track_info_.video().duration;
    }
    case MediaType::AUDIO: {
      return track_info_.audio().duration;
    }
    default: {
      return base::TimeDelta::Zero();
    }
  }
}

MediaFormat& MediaFormat::SetWidth(const int16_t width) {
  if (stream_type_ != MediaType::VIDEO) {
    AVE_LOG(LS_WARNING) << "SetWidth failed, stream type is not video";
  } else {
    track_info_.video().width = width;
  }
  return *this;
}

int16_t MediaFormat::width() const {
  if (stream_type_ != MediaType::VIDEO) {
    AVE_LOG(LS_WARNING) << "width failed, stream type is not video";
    return -1;
  }
  return track_info_.video().width;
}

MediaFormat& MediaFormat::SetHeight(const int16_t height) {
  if (stream_type_ != MediaType::VIDEO) {
    AVE_LOG(LS_WARNING) << "SetHeight failed, stream type is not video";
  } else {
    track_info_.video().height = height;
  }
  return *this;
}

int16_t MediaFormat::height() const {
  if (stream_type_ != MediaType::VIDEO) {
    AVE_LOG(LS_WARNING) << "height failed, stream type is not video";
    return -1;
  }
  return track_info_.video().height;
}

MediaFormat& MediaFormat::SetStride(const int16_t stride) {
  if (stream_type_ != MediaType::VIDEO) {
    AVE_LOG(LS_WARNING) << "SetStride failed, stream type is not video";
  } else {
    track_info_.video().stride = stride;
  }
  return *this;
}

int16_t MediaFormat::stride() const {
  if (stream_type_ != MediaType::VIDEO) {
    AVE_LOG(LS_WARNING) << "stride failed, stream type is not video";
    return -1;
  }
  return track_info_.video().stride;
}

MediaFormat& MediaFormat::SetPixelFormat(const PixelFormat pixel_format) {
  if (stream_type_ != MediaType::VIDEO) {
    AVE_LOG(LS_WARNING) << "SetPixelFormat failed, stream type is not video";
  } else {
    track_info_.video().pixel_format = pixel_format;
  }
  return *this;
}

PixelFormat MediaFormat::pixel_format() const {
  if (stream_type_ != MediaType::VIDEO) {
    AVE_LOG(LS_WARNING) << "pixel_format failed, stream type is not video";
    return PixelFormat::AVE_PIX_FMT_NONE;
  }
  return track_info_.video().pixel_format;
}

MediaFormat& MediaFormat::SetRotation(const int16_t rotation) {
  if (stream_type_ != MediaType::VIDEO) {
    AVE_LOG(LS_WARNING) << "SetRotation failed, stream type is not video";
  } else {
    track_info_.video().rotation = rotation;
  }
  return *this;
}

int16_t MediaFormat::rotation() const {
  if (stream_type_ != MediaType::VIDEO) {
    AVE_LOG(LS_WARNING) << "rotation failed, stream type is not video";
    return -1;
  }
  return track_info_.video().rotation;
}

MediaFormat& MediaFormat::SetSampleRate(const uint32_t sample_rate_hz) {
  if (stream_type_ != MediaType::AUDIO) {
    AVE_LOG(LS_WARNING) << "SetSampleRate failed, stream type is not audio";
  } else {
    track_info_.audio().sample_rate_hz = sample_rate_hz;
  }
  return *this;
}

uint32_t MediaFormat::sample_rate() const {
  if (stream_type_ != MediaType::AUDIO) {
    AVE_LOG(LS_WARNING) << "sample_rate failed, stream type is not audio";
    return -1;
  }
  return track_info_.audio().sample_rate_hz;
}

MediaFormat& MediaFormat::SetChannelLayout(const ChannelLayout channel_layout) {
  if (stream_type_ != MediaType::AUDIO) {
    AVE_LOG(LS_WARNING) << "SetChannelLayout failed, stream type is not audio";
  } else {
    track_info_.audio().channel_layout = channel_layout;
  }
  return *this;
}

ChannelLayout MediaFormat::channel_layout() const {
  if (stream_type_ != MediaType::AUDIO) {
    AVE_LOG(LS_WARNING) << "channel_layout failed, stream type is not audio";
    return CHANNEL_LAYOUT_NONE;
  }
  return track_info_.audio().channel_layout;
}

MediaFormat& MediaFormat::SetSamplesPerChannel(
    const int64_t samples_per_channel) {
  if (stream_type_ != MediaType::AUDIO) {
    AVE_LOG(LS_WARNING)
        << "SetSamplesPerChannel failed, stream type is not audio";
  } else {
    track_info_.audio().samples_per_channel = samples_per_channel;
  }
  return *this;
}

int64_t MediaFormat::samples_per_channel() const {
  if (stream_type_ != MediaType::AUDIO) {
    AVE_LOG(LS_WARNING)
        << "samples_per_channel failed, stream type is not audio";
    return -1;
  }
  return track_info_.audio().samples_per_channel;
}

MediaFormat& MediaFormat::SetBitsPerSample(const int16_t bits_per_sample) {
  if (stream_type_ != MediaType::AUDIO) {
    AVE_LOG(LS_WARNING) << "SetBitsPerSample failed, stream type is not audio";
  } else {
    track_info_.audio().bits_per_sample = bits_per_sample;
  }
  return *this;
}

int16_t MediaFormat::bits_per_sample() const {
  if (stream_type_ != MediaType::AUDIO) {
    AVE_LOG(LS_WARNING) << "bits_per_sample failed, stream type is not audio";
    return -1;
  }
  return track_info_.audio().bits_per_sample;
}

std::shared_ptr<Message>& MediaFormat::meta() {
  if (!meta_) {
    meta_ = std::make_shared<Message>();
  }
  return meta_;
}

}  // namespace media
}  // namespace ave
