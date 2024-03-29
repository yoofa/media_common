/*
 * Looper.cc
 * Copyright (C) 2021 youfa.song <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#include "looper.h"

#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "../base/count_down_latch.h"
#include "handler_roster.h"
#include "message.h"

namespace ave {

HandlerRoster gRoster;

Looper::Looper()
    : thread_(nullptr), looping_(false), start_latch_(1), stopped_(false) {}

Looper::~Looper() {
  stop();
}

void Looper::setName(std::string name) {
  name_ = name;
}

Looper::handler_id Looper::registerHandler(
    const std::shared_ptr<Handler> handler) {
  return gRoster.registerHandler(shared_from_this(), handler);
}

void Looper::unregisterHandler(handler_id handler_id) {
  gRoster.unregisterHandler(handler_id);
}

int32_t Looper::start(int32_t priority) {
  std::lock_guard<std::mutex> guard(mutex_);
  if (thread_.get()) {
    return -1;
  }

  thread_ = std::make_unique<std::thread>(&Looper::loop, this);
  looping_ = true;
  start_latch_.Wait();
  return 0;
}

int32_t Looper::stop() {
  // TODO(youfa) support stop in loop thread.
  {
    std::lock_guard<std::mutex> guard(mutex_);
    stopped_ = true;
    looping_ = false;
    condition_.notify_all();
  }
  if (thread_.get()) {
    thread_->join();
    thread_.release();
  }
  return 0;
}

void Looper::post(const std::shared_ptr<Message>& message,
                  const int64_t delayUs) {
  std::lock_guard<std::mutex> guard(mutex_);
  if (stopped_) {
    return;
  }
  int64_t whenUs;
  if (delayUs > 0) {
    int64_t nowUs = getNowUs();
    whenUs = (delayUs > (std::numeric_limits<int64_t>::max() - nowUs)
                  ? std::numeric_limits<int64_t>::max()
                  : (nowUs + delayUs));
  } else {
    whenUs = getNowUs();
  }

  std::unique_ptr<Event> event = std::make_unique<Event>();
  event->when_us_ = whenUs;
  event->message_ = std::move(message);
  event_queue_.push(std::move(event));
  condition_.notify_all();
}

void Looper::loop() {
  start_latch_.CountDown();
  while (keepRunning()) {
    std::shared_ptr<Message> message;
    {
      std::unique_lock<std::mutex> l(mutex_);

      if (event_queue_.size() == 0) {
        condition_.wait(l);
        continue;
      }

      auto& event = event_queue_.top();
      int64_t nowUs = getNowUs();

      if (event->when_us_ > nowUs) {
        int64_t delayUs = event->when_us_ - nowUs;
        if (delayUs > std::numeric_limits<int64_t>::max()) {
          delayUs = std::numeric_limits<int64_t>::max();
        }

        condition_.wait_for(l, std::chrono::microseconds(delayUs));
        continue;
      }

      message = std::move(event->message_);
      event_queue_.pop();
    }
    message->deliver();
    message.reset();
  }
}

bool Looper::keepRunning() {
  std::lock_guard<std::mutex> l(mutex_);
  return looping_ || (event_queue_.size() > 0);
}

std::shared_ptr<ReplyToken> Looper::createReplyToken() {
  return std::make_shared<ReplyToken>(shared_from_this());
}

status_t Looper::awaitResponse(const std::shared_ptr<ReplyToken>& replyToken,
                               std::shared_ptr<Message>& response) {
  std::unique_lock<std::mutex> guard(mutex_);
  // AVE_CHECK(replyToken != NULL)
  while (!replyToken->getReply(response)) {
    replies_condition_.wait(guard);
  }

  return 0;
}

status_t Looper::postReply(const std::shared_ptr<ReplyToken>& replyToken,
                           const std::shared_ptr<Message>& reply) {
  std::lock_guard<std::mutex> guard(mutex_);
  status_t err = replyToken->setReply(reply);
  if (err == 0) {
    replies_condition_.notify_all();
  }
  return err;
}

}  // namespace ave
