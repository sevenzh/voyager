// Copyright (c) 2016 Mirants Lu. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "voyager/rpc/rpc_codec.h"

namespace voyager {

bool RpcCodec::ParseFromBuffer(Buffer* buf,
                               google::protobuf::Message* message) {
  if (buf->ReadableSize() >= kHeaderSize) {
    int size;
    memcpy(&size, buf->Peek(), kHeaderSize);
    if (buf->ReadableSize() >= static_cast<size_t>(size)) {
      message->ParseFromArray(buf->Peek() + kHeaderSize, size - kHeaderSize);
      buf->Retrieve(size);
      return true;
    }
  }
  return false;
}

bool RpcCodec::SerializeToString(const google::protobuf::Message& message,
                                 std::string* s) {
  char buf[kHeaderSize];
  int size = message.ByteSize() + kHeaderSize;
  memcpy(buf, &size, kHeaderSize);
  s->append(buf, kHeaderSize);
  return message.AppendToString(s);
}

}  // namespace voyager
