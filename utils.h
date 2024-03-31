/*
 * utils.h
 * Copyright (C) 2022 youfa.song <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#ifndef UTILS_H
#define UTILS_H

#include <memory>

#include "base/errors.h"
#include "message.h"
#include "meta_data.h"

namespace ave {
status_t convertMetaDataToMessage(const MetaData* meta,
                                  std::shared_ptr<Message>& format);

status_t convertMetaDataToMessage(const std::shared_ptr<MetaData>& meta,
                                  std::shared_ptr<Message>& format);

status_t convertMessageToMetaData(const std::shared_ptr<Message>& format,
                                  std::shared_ptr<MetaData>& meta);

// Returns a pointer to the next NAL start code in buffer of size |length|
// starting at |data|, or a pointer to the end of the buffer if the start code
// is not found.
// TODO: combine this with avc_utils::getNextNALUnit
const uint8_t* findNextNalStartCode(const uint8_t* data, size_t length);

struct HLSTime {
  int32_t seq_;
  int64_t time_us_;
  std::shared_ptr<Message> meta_;

  explicit HLSTime(const std::shared_ptr<Message>& meta = NULL);
  int64_t getSegmentTimeUs() const;
};

bool operator<(const HLSTime& t0, const HLSTime& t1);

} /* namespace ave */

#endif /* !UTILS_H */
