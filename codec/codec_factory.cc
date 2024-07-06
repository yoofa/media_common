/*
 * codec_factory.cc
 * Copyright (C) 2024 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#include "codec_factory.h"

#include <list>
#include <memory>
#include "media/codec/codec.h"

namespace ave {
namespace media {

std::list<std::shared_ptr<CodecFactory>> gCodecFactories;

status_t registerCodecFactory(std::shared_ptr<CodecFactory> factory) {
  // insert with priority
  auto it = gCodecFactories.begin();
  for (; it != gCodecFactories.end(); it++) {
    if (factory->priority() > (*it)->priority()) {
      break;
    }
  }
  gCodecFactories.insert(it, factory);
  return OK;
}

std::shared_ptr<Codec> createCodecByType(CodecId codec_id, bool encoder) {
  for (auto factory : gCodecFactories) {
    auto codec = factory->createCodecByType(codec_id, encoder);
    if (codec) {
      return codec;
    }
  }
  return nullptr;
}

std::shared_ptr<Codec> createCodecByName(std::string& name) {
  for (auto factory : gCodecFactories) {
    auto codec = factory->createCodecByName(name);
    if (codec) {
      return codec;
    }
  }
  return nullptr;
}

}  // namespace media
}  // namespace ave