#pragma once

#include <memory>

#include "messages/Message.hpp"

namespace iex::iexequities::tops::iextp::v1_66 {

// Makes the message a Message Type selects. A code the specification does
// not list makes an UnknownMessage carrying that code, never nothing, so a stream never
// stops on one.
class Factory {
  public:
    static std::unique_ptr<Message> create(MessageCode code);
};

} // namespace iex::iexequities::tops::iextp::v1_66
