/*
 * audio_device_factory.h
 * Copyright (C) 2024 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#ifndef AUDIO_DEVICE_FACTORY_H
#define AUDIO_DEVICE_FACTORY_H

#include <memory>

namespace ave {
namespace media {

class AudioTrack;
class AudioRecord;

// AudioDeviceFactory is a factory class for creating AudioDevice objects.
// AudioDevice can open AudioTrack and AudioRecord objects.
class AudioDeviceFactory {
  // create an AudioTrack object.
  virtual std::shared_ptr<AudioTrack> createAudioTrack() = 0;

  // create an AudioRecord object.
  virtual std::shared_ptr<AudioRecord> createAudioRecord() = 0;

  // set audio input device

  // set audio output device
};

}  // namespace media
}  // namespace ave

#endif /* !AUDIO_DEVICE_FACTORY_H */
