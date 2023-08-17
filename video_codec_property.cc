/*
 * video_codec_property.cc
 * Copyright (C) 2023 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#include "video_codec_property.h"

#include "base/checks.h"

namespace avp {

namespace {
constexpr char kPayloadNameVp8[] = "VP8";
constexpr char kPayloadNameVp9[] = "VP9";
constexpr char kPayloadNameAv1[] = "AV1X";
constexpr char kPayloadNameH264[] = "H264";
constexpr char kPayloadNameH265[] = "H265";
constexpr char kPayloadNameGeneric[] = "Generic";
// constexpr char kPayloadNameMultiplex[] = "Multiplex";
}  // namespace

VideoCodecProperty::VideoCodecProperty()
    : codec_id(CodecId::AV_CODEC_ID_NONE),
      mode(VideoCodecMode::kRealtimeVideo),
      width(0),
      height(0),
      bit_rate(0),
      bit_rate_range({0, 0}),
      frame_rate(0),
      qp_range({0, 0}) {}

H264Specific* VideoCodecProperty::H264() {
  DCHECK(codec_id == CodecId::AV_CODEC_ID_H264);
  return std::get_if<H264Specific>(&specific_data_);
}

const H264Specific& VideoCodecProperty::H264() const {
  DCHECK(codec_id == CodecId::AV_CODEC_ID_H264);
  return std::get<H264Specific>(specific_data_);
}

H265Specific* VideoCodecProperty::H265() {
  DCHECK(codec_id == CodecId::AV_CODEC_ID_H265);
  return std::get_if<H265Specific>(&specific_data_);
}

const H265Specific& VideoCodecProperty::H265() const {
  DCHECK(codec_id == CodecId::AV_CODEC_ID_H265);
  return std::get<H265Specific>(specific_data_);
}

VP8Specific* VideoCodecProperty::VP8() {
  DCHECK(codec_id == CodecId::AV_CODEC_ID_VP8);
  return std::get_if<VP8Specific>(&specific_data_);
}

const VP8Specific& VideoCodecProperty::VP8() const {
  DCHECK(codec_id == CodecId::AV_CODEC_ID_VP8);
  return std::get<VP8Specific>(specific_data_);
}

VP9Specific* VideoCodecProperty::VP9() {
  DCHECK(codec_id == CodecId::AV_CODEC_ID_VP9);
  return std::get_if<VP9Specific>(&specific_data_);
}

const VP9Specific& VideoCodecProperty::VP9() const {
  DCHECK(codec_id == CodecId::AV_CODEC_ID_VP9);
  return std::get<VP9Specific>(specific_data_);
}

const char* CodecName(CodecId type) {
  switch (type) {
    case CodecId::AV_CODEC_ID_VP8:
      return kPayloadNameVp8;
    case CodecId::AV_CODEC_ID_VP9:
      return kPayloadNameVp9;
    case CodecId::AV_CODEC_ID_AV1:
      return kPayloadNameAv1;
    case CodecId::AV_CODEC_ID_H264:
      return kPayloadNameH264;
    case CodecId::AV_CODEC_ID_H265:
      return kPayloadNameH265;
    default:
      return kPayloadNameGeneric;
  }
}

}  // namespace avp
