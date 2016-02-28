#ifndef MIRANTS_CORE_EVENT_SELECT_H_
#define MIRANTS_CORE_EVENT_SELECT_H_

#include <sys/select.h>

#include "mirants/core/event_poller.h"

namespace mirants {

class EventSelect : public EventPoller{
 public:
  EventSelect(EventLoop* ev);
  virtual ~EventSelect();
  virtual void Poll();
  virtual void RemoveDispatch(Dispatch* dispatch); 
  virtual void UpdateDispatch(Dispatch* dispatch);
};

}  // namespace mirants

#endif  // MIRANTS_CORE_EVENT_SELECT_H_