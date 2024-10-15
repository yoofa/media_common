/*
 * ffmpeg_codec_utils.cc
 * Copyright (C) 2024 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#include "ffmpeg_codec_utils.h"
#include "third_party/ffmpeg/libavcodec/codec_id.h"

extern "C" {
#include <libavcodec/avcodec.h>
}

namespace ave {
namespace media {

CodecId ConvertToAVECodecId(const AVCodecID& ffmpeg_codec_id) {
  switch (ffmpeg_codec_id) {
    /* video codecs */
    case AV_CODEC_ID_H264: {
      return CodecId::AVE_CODEC_ID_H264;
    };
    case AV_CODEC_ID_MPEG4: {
      return CodecId::AVE_CODEC_ID_MPEG4;
    };
    case AV_CODEC_ID_MPEG2VIDEO: {
      return CodecId::AVE_CODEC_ID_MPEG2VIDEO;
    };
    case AV_CODEC_ID_VP8: {
      return CodecId::AVE_CODEC_ID_VP8;
    };
    case AV_CODEC_ID_VP9: {
      return CodecId::AVE_CODEC_ID_VP9;
    };
    case AV_CODEC_ID_HEVC: {
      return CodecId::AVE_CODEC_ID_HEVC;
    };
    case AV_CODEC_ID_AV1: {
      return CodecId::AVE_CODEC_ID_AV1;
    };

    /* audio codecs */
    case AV_CODEC_ID_MP3: {
      return CodecId::AVE_CODEC_ID_MP3;
    }
    case AV_CODEC_ID_AAC: {
      return CodecId::AVE_CODEC_ID_AAC;
    }
    case AV_CODEC_ID_AC3: {
      return CodecId::AVE_CODEC_ID_AC3;
    }
    case AV_CODEC_ID_EAC3: {
      return CodecId::AVE_CODEC_ID_EAC3;
    }

      /* subtitle codecs */

    default: {
      return CodecId::AVE_CODEC_ID_NONE;
    }
  }
}

AVCodecID ConvertToFFmpegCodecId(const CodecId& codec_id) {
  switch (codec_id) {
    // video codecs
    case CodecId::AVE_CODEC_ID_H264: {
      return AV_CODEC_ID_H264;
    };
    case CodecId::AVE_CODEC_ID_MPEG4: {
      return AV_CODEC_ID_MPEG4;
    };
    case CodecId::AVE_CODEC_ID_MPEG2VIDEO: {
      return AV_CODEC_ID_MPEG2VIDEO;
    };
    case CodecId::AVE_CODEC_ID_VP8: {
      return AV_CODEC_ID_VP8;
    };
    case CodecId::AVE_CODEC_ID_VP9: {
      return AV_CODEC_ID_VP9;
    };
    case CodecId::AVE_CODEC_ID_HEVC: {
      return AV_CODEC_ID_HEVC;
    };
    case CodecId::AVE_CODEC_ID_AV1: {
      return AV_CODEC_ID_AV1;
    };

    // audio codecs
    case CodecId::AVE_CODEC_ID_MP3: {
      return AV_CODEC_ID_MP3;
    }
    case CodecId::AVE_CODEC_ID_AAC: {
      return AV_CODEC_ID_AAC;
    }
    case CodecId::AVE_CODEC_ID_AC3: {
      return AV_CODEC_ID_AC3;
    }
    case CodecId::AVE_CODEC_ID_EAC3: {
      return AV_CODEC_ID_EAC3;
    }

    // subtitle codecs
    default: {
      return AV_CODEC_ID_NONE;
    }
  }
}

}  // namespace media
}  // namespace ave
