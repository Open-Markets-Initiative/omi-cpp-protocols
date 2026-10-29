#pragma once

#include <memory>

#include "messages/Message.hpp"
#include "messages/MktdataPayload.hpp"
#include "messages/MdpsessionmgmtPayload.hpp"
#include "messages/ClientTcpMessage.hpp"
#include "messages/ServerTcpMessage.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

// Makes the message a Schema Id selects. A code the specification does
// not list makes an UnknownMessage carrying that code, never nothing, so a stream never
// stops on one.
class Factory {
  public:
    static std::unique_ptr<Message> create(MessageCode code);
};

// Makes the message a Template Id selects. A code the specification does
// not list makes an UnknownMktdataPayload carrying that code, never nothing, so a stream never
// stops on one.
class MktdataPayloadFactory {
  public:
    static std::unique_ptr<MktdataPayload> create(MktdataPayloadCode code);
};

// Makes the message a Template Id selects. A code the specification does
// not list makes an UnknownMdpsessionmgmtPayload carrying that code, never nothing, so a stream never
// stops on one.
class MdpsessionmgmtPayloadFactory {
  public:
    static std::unique_ptr<MdpsessionmgmtPayload> create(MdpsessionmgmtPayloadCode code);
};

// Makes the message a Template Id selects. A code the specification does
// not list makes an UnknownClientTcpMessage carrying that code, never nothing, so a stream never
// stops on one.
class ClientTcpMessageFactory {
  public:
    static std::unique_ptr<ClientTcpMessage> create(ClientTcpMessageCode code);
};

// Makes the message a Template Id selects. A code the specification does
// not list makes an UnknownServerTcpMessage carrying that code, never nothing, so a stream never
// stops on one.
class ServerTcpMessageFactory {
  public:
    static std::unique_ptr<ServerTcpMessage> create(ServerTcpMessageCode code);
};

} // namespace cme::globex::mdp3::sbe::v1_5
