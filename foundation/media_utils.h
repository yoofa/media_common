/*
 * media_utils.h
 * Copyright (C) 2023 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#ifndef MEDIA_UTILS_H
#define MEDIA_UTILS_H

#include <sys/types.h>

#include "../codec/codec_id.h"
#include "pixel_format.h"

namespace ave {

enum class MediaType {
  UNKNOWN = -1,  ///< Usually treated as MEDIA_TYPE_DATA
  VIDEO,
  AUDIO,
  DATA,  ///< Opaque data information usually continuous
  SUBTITLE,
  ATTACHMENT,  ///< Opaque data information usually sparse
  NB,
};

enum class PictureType {
  NONE = -1,
  I,
  P,
  B,
  S,
  SI,
  SP,
  BI,
  D,
};

const char* get_media_type_string(enum MediaType media_type);

struct AudioSampleInfo {
  CodecId codec_id = CodecId::AV_CODEC_ID_NONE;
  int64_t timestamp_us = -1;
  int64_t sample_rate_hz = -1;
  int16_t channels = -1;
  int64_t samples_per_channel = -1;
  int16_t bits_per_sample = -1;
};

struct VideoSampleInfo {
  CodecId codec_id = CodecId::AV_CODEC_ID_NONE;
  // pts
  int64_t timestamp_us = -1;
  int64_t dts_us = -1;
  int16_t stride = -1;
  int16_t width = -1;
  int16_t height = -1;
  int16_t rotation = -1;
  PixelFormat pixel_format = PixelFormat::AV_PIX_FMT_NONE;

  // encoded
  PictureType picture_type = PictureType::NONE;
  int16_t qp = -1;
};

}  // namespace ave
#endif /* !MEDIA_UTILS_H */
