#pragma once

#include <memory>

#include "messages/Message.hpp"

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

// Makes the message a Message Type selects. A code the specification does
// not list makes an UnknownMessage carrying that code, never nothing, so a stream never
// stops on one.
class Factory {
  public:
    static std::unique_ptr<Message> create(MessageCode code);
};

} // namespace nyse::texasequities::integratedfeed::pillar::v2_5_g
