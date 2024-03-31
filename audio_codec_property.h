/*
 * audio_codec_property.h
 * Copyright (C) 2023 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#ifndef AUDIO_CODEC_PROPERTY_H
#define AUDIO_CODEC_PROPERTY_H

#include "base/types.h"

#include "codec_id.h"

namespace ave {

class AudioCodecProperty {
 public:
  AudioCodecProperty();
  CodecId codec_id;

  size_t channels;
  size_t samples_per_channel;
  int sample_rate;

  uint32_t bit_rate;
};
}  // namespace ave

#endif /* !AUDIO_CODEC_PROPERTY_H */
