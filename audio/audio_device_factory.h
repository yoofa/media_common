/*
 * audio_device_factory.h
 * Copyright (C) 2024 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#ifndef AUDIO_DEVICE_FACTORY_H
#define AUDIO_DEVICE_FACTORY_H

#include <memory>

#include "base/errors.h"

namespace ave {
namespace media {

struct AudioDeviceInfo {};

class AudioTrack;
class AudioRecord;

// AudioDeviceFactory is a factory class for creating AudioDevice objects.
// AudioDevice can open AudioTrack and AudioRecord objects.
class AudioDeviceFactory {
  // create an AudioTrack object.
  virtual std::shared_ptr<AudioTrack> createAudioTrack() = 0;

  // create an AudioRecord object.
  virtual std::shared_ptr<AudioRecord> createAudioRecord() = 0;

  // get supported audio devices
  // return <device_id, device_info>
  virtual std::vector<std::pair<int, AudioDeviceInfo>>
  getSupportedAudioDevices() = 0;

  // set audio input device
  virtual status_t setAudioInputDevice(int device_id) = 0;

  // set audio output device
  virtual status_t setAudioOutputDevice(int device_id) = 0;
};

}  // namespace media
}  // namespace ave

#endif /* !AUDIO_DEVICE_FACTORY_H */
