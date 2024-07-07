/*
 * alsa_audio_track.h
 * Copyright (C) 2024 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#ifndef ALSA_AUDIO_TRACK_H
#define ALSA_AUDIO_TRACK_H

#include "../audio_track.h"

namespace ave {
namespace media {

class AlsaAudioTrack : public AudioTrack {};
}  // namespace media
}  // namespace ave

#endif /* !ALSA_AUDIO_TRACK_H */
