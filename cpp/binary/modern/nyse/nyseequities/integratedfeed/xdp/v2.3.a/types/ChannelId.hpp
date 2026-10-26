#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {


// The ID of the multicast channel over which the packet was sent.
struct ChannelId {

    static constexpr auto name = "Channel Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ChannelId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ChannelId(const std::uint8_t &value)
     : value{ value } {}

    // get value of ChannelId field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
