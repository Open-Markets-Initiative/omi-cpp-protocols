#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {


// A flag that indicates whether this is an original, retransmitted, or ‘replayed’ message.
struct DeliveryFlag {

    static constexpr auto name = "Delivery Flag";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr DeliveryFlag()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit DeliveryFlag(const std::uint8_t &value)
     : value{ value } {}

    // get value of DeliveryFlag field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
