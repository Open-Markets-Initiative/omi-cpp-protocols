#pragma once

#include <memory>

#include "messages/Message.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// Makes the message a Template Id selects. A code the specification does
// not list makes an UnknownMessage carrying that code, never nothing, so a stream never
// stops on one.
class Factory {
  public:
    static std::unique_ptr<Message> create(MessageCode code);
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
