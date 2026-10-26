#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Number of decimals in price (256=fractions)
struct DecimalsInPrice {

    static constexpr const char* name = "Decimals In Price";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr DecimalsInPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit DecimalsInPrice(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of DecimalsInPrice field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
