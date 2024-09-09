/*
 * media_clock.h
 * Copyright (C) 2024 youfa <vsyfar@gmail.com>
 *
 * Distributed under terms of the GPLv2 license.
 */

#ifndef MEDIA_CLOCK_H
#define MEDIA_CLOCK_H

#include <functional>
#include <list>
#include <mutex>

#include "base/errors.h"
#include "base/task_util/task_runner.h"
#include "base/thread_annotation.h"

namespace ave {
namespace media {

using ave::base::TaskRunner;

class MediaClock {
 public:
  enum TimerReason {
    TIMER_REASON_REACHED = 0,
    TIMER_REASON_RESET = 1,
  };
  struct TimerEvent {
    virtual void OnTimerEvent(TimerReason reason) = 0;
  };
  struct Callback {
    virtual void OnDiscontinuity(int64_t anchor_media_us,
                                 int64_t anchor_real_us,
                                 float playback_rate) = 0;
  };

  explicit MediaClock();
  ~MediaClock();

  void SetStartingTimeMedia(int64_t starting_time_media_us);
  void ClearAnchor();
  void UpdateAnchor(int64_t anchor_time_media_us,
                    int64_t anchor_time_real_us,
                    int64_t max_time_media_us = INT64_MAX);
  void UpdateMaxTimeMedia(int64_t max_time_media_us);
  void SetPlaybackRate(float rate);
  float GetPlaybackRate() const;
  status_t GetMediaTime(int64_t real_us,
                        int64_t* out_media_us,
                        bool allow_past_max_time = false) const;
  status_t GetRealTimeFor(int64_t target_media_us, int64_t* out_real_us) const;
  void AddTimerEvent(std::function<void(TimerReason)> callback,
                     int64_t media_time_us,
                     int64_t adjust_real_us = 0);
  void SetNotificationCallback(Callback* callback);

 private:
  struct Timer {
    Timer(std::function<void(TimerReason)> callback,
          int64_t media_time_us,
          int64_t adjust_real_us)
        : callback(std::move(callback)),
          media_time_us(media_time_us),
          adjust_real_us(adjust_real_us) {}

    std::function<void(TimerReason)> callback = nullptr;
    int64_t media_time_us = 0;
    int64_t adjust_real_us = 0;
  };

  status_t GetMediaTime_l(int64_t real_us,
                          int64_t* out_media_us,
                          bool allow_past_max_time) const REQUIRES(mutex_);

  void Reset();

  void ProcessTimers() REQUIRES(mutex_);
  void PostProcessTimers(int64_t delay_us = 0);
  void UpdateAnchorTimesAndPlaybackRate(int64_t anchor_time_media_us,
                                        int64_t anchor_time_real_us,
                                        float playback_rate) REQUIRES(mutex_);
  void NotifyDiscontinuity() REQUIRES(mutex_);

  std::unique_ptr<TaskRunner> task_runner_;
  mutable std::mutex mutex_;
  int64_t starting_time_media_us_ GUARDED_BY(mutex_);
  int64_t anchor_time_media_us_ GUARDED_BY(mutex_);
  int64_t anchor_time_real_us_ GUARDED_BY(mutex_);
  int64_t max_time_media_us_ GUARDED_BY(mutex_);
  float playback_rate_ GUARDED_BY(mutex_);
  Callback* notify_callback_;
  std::list<Timer> timers_ GUARDED_BY(mutex_);
};

}  // namespace media
}  // namespace ave

#endif /* !MEDIA_CLOCK_H */
