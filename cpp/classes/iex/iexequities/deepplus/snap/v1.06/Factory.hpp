#pragma once

#include <memory>

#include "messages/Message.hpp"
#include "messages/IexTpMessageData.hpp"

namespace iex::iexequities::deepplus::snap::v1_06 {

// Makes the message a Message Type selects. A code the specification does
// not list makes an UnknownMessage carrying that code, never nothing, so a stream never
// stops on one.
class Factory {
  public:
    static std::unique_ptr<Message> create(MessageCode code);
};

// Makes the message a Iex Tp Message Type selects. A code the specification does
// not list makes an UnknownIexTpMessageData carrying that code, never nothing, so a stream never
// stops on one.
class IexTpMessageDataFactory {
  public:
    static std::unique_ptr<IexTpMessageData> create(IexTpMessageDataCode code);
};

} // namespace iex::iexequities::deepplus::snap::v1_06
