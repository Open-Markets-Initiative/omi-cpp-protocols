#pragma once

#include <memory>

#include "messages/Message.hpp"
#include "messages/Data.hpp"
#include "messages/TcpMessage.hpp"
#include "messages/UnsequencedMessage.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Makes the message a Mach Packet Type selects. A code the specification does
// not list makes an UnknownMessage carrying that code, never nothing, so a stream never
// stops on one.
class Factory {
  public:
    static std::unique_ptr<Message> create(MessageCode code);
};

// Makes the message a Message Type selects. A code the specification does
// not list makes an UnknownData carrying that code, never nothing, so a stream never
// stops on one.
class DataFactory {
  public:
    static std::unique_ptr<Data> create(DataCode code);
};

// Makes the message a Esesm Packet Type selects. A code the specification does
// not list makes an UnknownTcpMessage carrying that code, never nothing, so a stream never
// stops on one.
class TcpMessageFactory {
  public:
    static std::unique_ptr<TcpMessage> create(TcpMessageCode code);
};

// Makes the message a Unsequenced Message Type selects. A code the specification does
// not list makes an UnknownUnsequencedMessage carrying that code, never nothing, so a stream never
// stops on one.
class UnsequencedMessageFactory {
  public:
    static std::unique_ptr<UnsequencedMessage> create(UnsequencedMessageCode code);
};

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
