#pragma once

#include <memory>

#include "messages/Message.hpp"
#include "messages/Payload.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// Makes the message a Message Type selects. A code the specification does
// not list makes an UnknownMessage carrying that code, never nothing, so a stream never
// stops on one.
class Factory {
  public:
    static std::unique_ptr<Message> create(MessageCode code);
};

// Makes the message a Template Id selects. A code the specification does
// not list makes an UnknownPayload carrying that code, never nothing, so a stream never
// stops on one.
class PayloadFactory {
  public:
    static std::unique_ptr<Payload> create(PayloadCode code);
};

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
