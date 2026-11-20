// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: Factory.hpp
#pragma once

#include <memory>

#include "messages/Message.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Makes the message a Msg Type selects. A code the specification does
// not list makes an UnknownMessage carrying that code, never nothing, so a stream never
// stops on one.
class Factory {
  public:
    static std::unique_ptr<Message> create(MessageCode code);
};

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
