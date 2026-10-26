#pragma once

#include <cstddef>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {


// Market-data application message type carried over the SesM sequenced channel (matches the MACH UDP Message Type byte; Miax Options uses Ascii message codes)
struct SequencedMessageType {

    static constexpr auto name = "Sequenced Message Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SequencedMessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SequencedMessageType(const char &value)
     : value{ value } {}

    // get value of SequencedMessageType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
