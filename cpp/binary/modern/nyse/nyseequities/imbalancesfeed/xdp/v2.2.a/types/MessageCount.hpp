#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {


// The number of messages in this packet
struct MessageCount {

    static constexpr auto name = "Message Count";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MessageCount()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MessageCount(const std::uint8_t &value)
     : value{ value } {}

    // get value of MessageCount field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
