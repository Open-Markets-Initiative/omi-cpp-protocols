#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::itch::v1_7 {

// Minimum tradable price.
struct LowerPriceLimit {

    static constexpr const char* name = "Lower Price Limit";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 1;
    static constexpr double denominator = 10;
    using type = std::uint32_t;

    // default constructor
    constexpr LowerPriceLimit()
     : value{ 0 } {}

    // constructor for LowerPriceLimit field
    constexpr explicit LowerPriceLimit(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of LowerPriceLimit field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of LowerPriceLimit field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
