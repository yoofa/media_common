/*
 * media_utils.h
 * Copyright (C) 2023 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#ifndef MEDIA_UTILS_H
#define MEDIA_UTILS_H

namespace avp {

enum class MediaType {
  UNKNOWN = -1,  ///< Usually treated as MEDIA_TYPE_DATA
  VIDEO,
  AUDIO,
  DATA,  ///< Opaque data information usually continuous
  SUBTITLE,
  ATTACHMENT,  ///< Opaque data information usually sparse
  NB
};

const char* get_media_type_string(enum MediaType media_type);

}  // namespace avp
#endif /* !MEDIA_UTILS_H */
