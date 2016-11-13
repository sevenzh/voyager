#ifndef VOYAGER_PAXOS_NETWORK_H_
#define VOYAGER_PAXOS_NETWORK_H_

#include <functional>
#include <map>
#include <memory>

#include "voyager/paxos/options.h"
#include "voyager/paxos/nodeinfo.h"
#include "voyager/core/bg_eventloop.h"
#include "voyager/core/eventloop.h"
#include "voyager/core/sockaddr.h"
#include "voyager/core/tcp_client.h"
#include "voyager/core/tcp_server.h"

namespace voyager {
namespace paxos {

class Network {
 public:
  Network(const Options* options);

  void Start(const std::function<void (const char* s, size_t n)>& cb);
  void Stop();

  void SendMessage(const NodeInfo& other, const std::string& message);

 private:
  void SendMessageInLoop(const SockAddr& addr, const std::string& message);

  SockAddr addr_;
  BGEventLoop bg_loop_;
  EventLoop* loop_;
  std::unique_ptr<TcpServer> server_;
  std::map<std::string, TcpConnectionPtr> connection_map_;

  // No copying allowed
  Network(const Network&);
  void operator=(const Network&);
};

}  // namespace paxos
}  // namespace voyager

#endif   // VOYAGER_PAXOS_NETWORK_H_