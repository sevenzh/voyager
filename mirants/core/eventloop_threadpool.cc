#include "mirants/core/eventloop_threadpool.h"
#include "mirants/core/eventloop.h"
#include "mirants/core/eventloop_thread.h"
#include "mirants/util/stringprintf.h"
#include <stdio.h>
namespace mirants {

EventLoopThreadPool::EventLoopThreadPool(EventLoop* evloop, 
                                         const std::string& name,
                                         int size)
    : baseloop_(evloop),
      poolname_(name),
      size_(size),
      started_(false),
      next_(0),
      threads_(new scoped_ptr<EventLoopThread>[size]) {
}

EventLoopThreadPool::~EventLoopThreadPool() {
}

void EventLoopThreadPool::Start() {
  assert(!started_);
  baseloop_->AssertThreadSafe();
  started_ = true;
  for (int i = 0; i < size_; ++i) {
    EventLoopThread* ev_t = new EventLoopThread(
        StringPrintf("%s%d", poolname_.c_str(), i));
    threads_[i].reset(ev_t);
    eventloops_.push_back(ev_t->StartLoop());
  }
}

EventLoop* EventLoopThreadPool::GetNext() {
  baseloop_->AssertThreadSafe();
  assert(started_);
  if (eventloops_.empty()) {
    return baseloop_;
  }
  if (next_ >= static_cast<int>(eventloops_.size())) {
    next_ = 0;
  }
  return eventloops_[next_++];
}

}  // namespace mirants
