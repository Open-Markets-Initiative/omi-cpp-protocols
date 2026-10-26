#pragma once

#include <memory>

#include "messages/Message.hpp"
#include "messages/ServerMessage.hpp"
#include "messages/SequencedMessage.hpp"
#include "messages/PacketMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Makes the message a Client Packet Type selects. A code the specification does
// not list makes an UnknownMessage carrying that code, never nothing, so a stream never
// stops on one.
class Factory {
  public:
    static std::unique_ptr<Message> create(MessageCode code);
};

// Makes the message a Server Packet Type selects. A code the specification does
// not list makes an UnknownServerMessage carrying that code, never nothing, so a stream never
// stops on one.
class ServerMessageFactory {
  public:
    static std::unique_ptr<ServerMessage> create(ServerMessageCode code);
};

// Makes the message a Sequenced Message Type selects. A code the specification does
// not list makes an UnknownSequencedMessage carrying that code, never nothing, so a stream never
// stops on one.
class SequencedMessageFactory {
  public:
    static std::unique_ptr<SequencedMessage> create(SequencedMessageCode code);
};

// Makes the message a Message Type selects. A code the specification does
// not list makes an UnknownPacketMessage carrying that code, never nothing, so a stream never
// stops on one.
class PacketMessageFactory {
  public:
    static std::unique_ptr<PacketMessage> create(PacketMessageCode code);
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
