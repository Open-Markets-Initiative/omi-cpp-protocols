#pragma once

#include <memory>

#include "messages/Message.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Makes the message a Message Type selects. A code the specification does
// not list makes an UnknownMessage carrying that code, never nothing, so a stream never
// stops on one.
class Factory {
  public:
    static std::unique_ptr<Message> create(MessageCode code);
};

} // namespace lseg::lse::level2mbo::gtp::v26_2
