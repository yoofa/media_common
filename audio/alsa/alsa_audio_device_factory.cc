/*
 * alsa_audio_device_factory.cc
 * Copyright (C) 2024 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#include "alsa_audio_device_factory.h"

#include "base/attributes.h"

#include "../audio_record.h"
#include "../audio_track.h"

#include "alsa_audio_record.h"
#include "alsa_audio_track.h"

namespace ave {
namespace media {

std::shared_ptr<AudioTrack> AlsaAudioDeviceFactory::createAudioTrack() {
  return std::make_shared<AlsaAudioTrack>();
}

std::shared_ptr<AudioRecord> AlsaAudioDeviceFactory::createAudioRecord() {
  return std::make_shared<AlsaAudioRecord>();
}

std::vector<std::pair<int, AudioDeviceInfo>>
AlsaAudioDeviceFactory::getSupportedAudioDevices() {
  return {};
}

// TODO: implement, remove unused
status_t AlsaAudioDeviceFactory::setAudioInputDevice(
    int device_id AVE_MAYBE_UNUSED) {
  return OK;
}

// TODO: implement, remove unused
status_t AlsaAudioDeviceFactory::setAudioOutputDevice(
    int device_id AVE_MAYBE_UNUSED) {
  // TODO
  return OK;
}

}  // namespace media
}  // namespace ave
