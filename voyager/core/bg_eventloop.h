// Copyright (c) 2016 Mirants Lu. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef VOYAGER_CORE_BG_EVENTLOOP_H_
#define VOYAGER_CORE_BG_EVENTLOOP_H_

#include <string>

#include "voyager/port/mutex.h"
#include "voyager/port/thread.h"

namespace voyager {

class EventLoop;

class BGEventLoop {
 public:
  explicit BGEventLoop(const std::string& name = std::string());
  ~BGEventLoop();

  EventLoop* Loop();

 private:
  void ThreadFunc();

  EventLoop *eventloop_;
  port::Mutex mu_;
  port::Condition cond_;
  port::Thread thread_;

  // No copying allowed
  BGEventLoop(const BGEventLoop&);
  void operator=(const BGEventLoop&);
};

}  // namespace voyager

#endif  // VOYAGER_CORE_BG_EVENTLOOP_H_
