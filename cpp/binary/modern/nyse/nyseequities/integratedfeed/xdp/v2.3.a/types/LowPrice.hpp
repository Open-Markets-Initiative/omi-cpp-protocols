#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

// The exchange Low price of this stock for the day. Use the Price Scale in the symbol index msg.
struct LowPrice {

    static constexpr const char* name = "Low Price";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr LowPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LowPrice(const std::uint32_t value)
     : value{ value } {}

    // get value of LowPrice field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
