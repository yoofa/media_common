/*
 * alsa_audio_device_factory.h
 * Copyright (C) 2024 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#ifndef ALSA_AUDIO_DEVICE_FACTORY_H
#define ALSA_AUDIO_DEVICE_FACTORY_H

#include "../audio_device_factory.h"

namespace ave {
namespace media {

class AlsaAudioDeviceFactory : public AudioDeviceFactory {
 public:
  AlsaAudioDeviceFactory() = default;
  ~AlsaAudioDeviceFactory() = default;
  std::shared_ptr<AudioTrack> createAudioTrack() override;
  std::shared_ptr<AudioRecord> createAudioRecord() override;
  std::vector<std::pair<int, AudioDeviceInfo>> getSupportedAudioDevices()
      override;
  status_t setAudioInputDevice(int device_id) override;
  status_t setAudioOutputDevice(int device_id) override;
};

}  // namespace media
}  // namespace ave

#endif /* !ALSA_AUDIO_DEVICE_FACTORY_H */
