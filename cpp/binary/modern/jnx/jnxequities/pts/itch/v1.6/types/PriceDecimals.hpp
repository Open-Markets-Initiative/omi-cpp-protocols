#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::itch::v1_6 {

// Number of decimal places in price fields; value is 1.
struct PriceDecimals {

    static constexpr const char* name = "Price Decimals";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr PriceDecimals()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceDecimals(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of PriceDecimals field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
