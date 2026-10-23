#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {


// Market-data application message type carried over the ESesM sequenced channel (matches the MACH UDP Message Type byte)
struct SequencedMessageType {

    static constexpr auto name = "Sequenced Message Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SequencedMessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SequencedMessageType(const std::uint8_t &value)
     : value{ value } {}

    // get value of SequencedMessageType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
