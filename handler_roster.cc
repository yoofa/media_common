/*
 * HandlerRoster.cc
 * Copyright (C) 2021 youfa.song <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#include "handler_roster.h"

#include <memory>
#include <mutex>

#include "handler.h"
#include "looper.h"
#include "message.h"

namespace avp {

HandlerRoster::HandlerRoster() : next_handler_id_(1) {}

Looper::handler_id HandlerRoster::registerHandler(
    const std::shared_ptr<Looper> looper,
    const std::shared_ptr<Handler> handler) {
  std::lock_guard<std::mutex> guard(mutex_);
  if (handler->id() != 0) {
    return -1;
  }

  HandlerInfo info;
  info.looper_ = looper;
  info.handler_ = handler;
  Looper::handler_id handlerId = next_handler_id_++;
  handlers_.emplace(std::make_pair(handlerId, info));

  handler->setId(handlerId, looper);

  return handlerId;
}

void HandlerRoster::unregisterHandler(Looper::handler_id handlerId) {
  std::lock_guard<std::mutex> guard(mutex_);

  auto it = handlers_.find(handlerId);
  if (it != handlers_.end()) {
    HandlerInfo info = it->second;
    std::shared_ptr<Handler> handler = info.handler_.lock();
    if (handler.get() != nullptr) {
      handler->setId(0, std::weak_ptr<Looper>());
    }

    handlers_.erase(it);
  }
}

}  // namespace avp
