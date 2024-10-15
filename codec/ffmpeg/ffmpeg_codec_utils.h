/*
 * ffmpeg_codec_utils.h
 * Copyright (C) 2024 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#ifndef FFMPEG_CODEC_UTILS_H
#define FFMPEG_CODEC_UTILS_H

extern "C" {
#include <libavcodec/avcodec.h>
}

#include "../codec_id.h"

namespace ave {

namespace media {

CodecId ConvertToAVECodecId(const AVCodecID& ffmpeg_codec_id);

AVCodecID ConvertToFFmpegCodecId(const CodecId& codec_id);

}  // namespace media
}  // namespace ave

#endif /* !FFMPEG_CODEC_UTILS_H */
