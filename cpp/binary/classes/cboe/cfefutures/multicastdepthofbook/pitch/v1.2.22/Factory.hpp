#pragma once

#include <memory>

#include "messages/Message.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Makes the message a Message Type selects. A code the specification does
// not list makes an UnknownMessage carrying that code, never nothing, so a stream never
// stops on one.
class Factory {
  public:
    static std::unique_ptr<Message> create(MessageCode code);
};

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
