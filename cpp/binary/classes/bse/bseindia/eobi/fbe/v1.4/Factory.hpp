#pragma once

#include <memory>

#include "messages/Message.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Makes the message a Template Id selects. A code the specification does
// not list makes an UnknownMessage carrying that code, never nothing, so a stream never
// stops on one.
class Factory {
  public:
    static std::unique_ptr<Message> create(MessageCode code);
};

} // namespace bse::bseindia::eobi::fbe::v1_4
