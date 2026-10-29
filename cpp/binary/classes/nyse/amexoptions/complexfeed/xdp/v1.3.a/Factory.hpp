#pragma once

#include <memory>

#include "messages/Message.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// Makes the message a Message Type selects. A code the specification does
// not list makes an UnknownMessage carrying that code, never nothing, so a stream never
// stops on one.
class Factory {
  public:
    static std::unique_ptr<Message> create(MessageCode code);
};

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
