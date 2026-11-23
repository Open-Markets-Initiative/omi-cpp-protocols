// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: Factory.hpp
#pragma once

#include <memory>

#include "messages/Message.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// Makes the message a Msg Type selects. A code the specification does
// not list makes an UnknownMessage carrying that code, never nothing, so a stream never
// stops on one.
class Factory {
  public:
    static std::unique_ptr<Message> create(MessageCode code);
};

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
