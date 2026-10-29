#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {


// Code identifying this message type
struct MessageType {

    static constexpr auto name = "Message Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MessageType(const std::uint8_t &value)
     : value{ value } {}

    // get value of MessageType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
