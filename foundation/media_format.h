/*
 * media_format.h
 * Copyright (C) 2024 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#ifndef MEDIA_FORMAT_H
#define MEDIA_FORMAT_H

#include <cstdint>

#include "../audio/channel_layout.h"
#include "../codec/codec_id.h"
#include "base/units/time_delta.h"
#include "media_utils.h"
#include "message.h"

namespace ave {
namespace media {
class MediaFormat {
 public:
  MediaFormat();
  virtual ~MediaFormat() = default;

  MediaFormat& SetStreamType(const ave::media::MediaType stream_type);

  MediaFormat& SetCodec(const CodecId codec);
  CodecId codec() const;

  MediaFormat& SetBitrate(const int64_t bps);
  int64_t bitrate() const;

  MediaFormat& SetDuration(const base::TimeDelta duration);
  base::TimeDelta duration() const;

  // video
  MediaFormat& SetWidth(const int16_t width);
  int16_t width() const;
  MediaFormat& SetHeight(const int16_t height);
  int16_t height() const;
  MediaFormat& SetStride(const int16_t stride);
  int16_t stride() const;
  MediaFormat& SetPixelFormat(const PixelFormat pixel_format);
  PixelFormat pixel_format() const;
  MediaFormat& SetRotation(const int16_t rotation);
  int16_t rotation() const;

  // audio
  MediaFormat& SetSampleRate(const uint32_t sample_rate_hz);
  uint32_t sample_rate() const;
  MediaFormat& SetChannelLayout(const ChannelLayout channel_layout);
  ChannelLayout channel_layout() const;
  MediaFormat& SetSamplesPerChannel(const int64_t samples_per_channel);
  int64_t samples_per_channel() const;
  MediaFormat& SetBitsPerSample(const int16_t bits_per_sample);
  int16_t bits_per_sample() const;

  // meta data
  std::shared_ptr<Message>& meta();

 private:
  ave::media::MediaType stream_type_;
  MediaTrackInfo track_info_;
  std::shared_ptr<Message> meta_;
};

}  // namespace media
}  // namespace ave

#endif /* !MEDIA_FORMAT_H */
