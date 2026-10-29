#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

// The exchange high price of this stock for the day. Use the Price Scale in the symbol index msg.
struct HighPrice {

    static constexpr const char* name = "High Price";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr HighPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit HighPrice(const std::uint32_t value)
     : value{ value } {}

    // get value of HighPrice field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
