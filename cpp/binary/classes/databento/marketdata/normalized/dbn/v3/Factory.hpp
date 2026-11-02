#pragma once

#include <memory>

#include "messages/Message.hpp"
#include "messages/GatewayMessage.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

// Makes the message a Rtype selects. A code the specification does
// not list makes an UnknownMessage carrying that code, never nothing, so a stream never
// stops on one.
class Factory {
  public:
    static std::unique_ptr<Message> create(MessageCode code);
};

// Makes the message a Rtype selects. A code the specification does
// not list makes an UnknownGatewayMessage carrying that code, never nothing, so a stream never
// stops on one.
class GatewayMessageFactory {
  public:
    static std::unique_ptr<GatewayMessage> create(GatewayMessageCode code);
};

} // namespace databento::marketdata::normalized::dbn::v3
