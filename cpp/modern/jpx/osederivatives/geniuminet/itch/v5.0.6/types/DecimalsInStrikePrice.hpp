#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Decimals in Strike Price
struct DecimalsInStrikePrice {

    static constexpr const char* name = "Decimals In Strike Price";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr DecimalsInStrikePrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit DecimalsInStrikePrice(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of DecimalsInStrikePrice field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
