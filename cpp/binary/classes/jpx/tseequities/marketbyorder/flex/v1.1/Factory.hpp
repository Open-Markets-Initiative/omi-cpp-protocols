#pragma once

#include <memory>

#include "messages/Message.hpp"
#include "messages/TcpMessage.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Makes the message a Message Type selects. A code the specification does
// not list makes an UnknownMessage carrying that code, never nothing, so a stream never
// stops on one.
class Factory {
  public:
    static std::unique_ptr<Message> create(MessageCode code);
};

// Makes the message a Packet Type selects. A code the specification does
// not list makes an UnknownTcpMessage carrying that code, never nothing, so a stream never
// stops on one.
class TcpMessageFactory {
  public:
    static std::unique_ptr<TcpMessage> create(TcpMessageCode code);
};

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
