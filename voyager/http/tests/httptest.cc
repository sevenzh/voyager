// Copyright (c) 2016 Mirants Lu. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "voyager/http/http_server.h"

#include <stdio.h>

#include <functional>
#include <string>
#include <utility>
#include <iostream>

#include "voyager/http/http_request.h"
#include "voyager/http/http_response.h"
#include "voyager/core/eventloop.h"
#include "voyager/util/logging.h"

namespace voyager {

void HandleHttpRequest(HttpRequestPtr request, HttpResponse* response) {
  std::cout << request->RequestMessage().Peek() << std::endl;

  response->SetVersion(request->Version());
  response->SetStatusCode("200");
  response->SetReasonParse("OK");
  response->AddHeader("Content-Type", "text/html; charset=UTF-8");
  response->AddHeader("Content-Encoding", "UTF-8");
  response->AddHeader("Connection", "close");

  std::string s("Welcome to Voyager's WebServer!");
  char buf[32];
  snprintf(buf, sizeof(buf), "%zu", s.size());
  response->AddHeader("Content-Length", buf);
  response->SetBody(std::move(s));

  response->SetCloseState(true);
}

}

int main() {
  voyager::EventLoop ev;
  voyager::SockAddr addr(5666);
  voyager::HttpServer server(&ev, addr, "WebServer", 4);
  server.SetHttpCallback(std::bind(voyager::HandleHttpRequest,
                                   std::placeholders::_1,
                                   std::placeholders::_2));
  server.Start();
  ev.Loop();
  return 0;
}
