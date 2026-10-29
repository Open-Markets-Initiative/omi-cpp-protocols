#pragma once

#include <memory>

#include "messages/Message.hpp"
#include "messages/Data.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Makes the message a Packet Type selects. A code the specification does
// not list makes an UnknownMessage carrying that code, never nothing, so a stream never
// stops on one.
class Factory {
  public:
    static std::unique_ptr<Message> create(MessageCode code);
};

// Makes the message a Message Type selects. A code the specification does
// not list makes an UnknownData carrying that code, never nothing, so a stream never
// stops on one.
class DataFactory {
  public:
    static std::unique_ptr<Data> create(DataCode code);
};

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
