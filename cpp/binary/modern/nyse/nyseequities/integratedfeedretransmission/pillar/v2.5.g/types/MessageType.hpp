#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {

// The type of this message
struct MessageType {

    static constexpr const char* name = "Message Type";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr MessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MessageType(const std::uint16_t value)
     : value{ value } {}

    // get value of MessageType field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
