#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::itch::v1_6 {

// Maximum tradable price.
struct UpperPriceLimit {

    static constexpr const char* name = "Upper Price Limit";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 1;
    static constexpr double denominator = 10;
    using type = std::uint32_t;

    // default constructor
    constexpr UpperPriceLimit()
     : value{ 0 } {}

    // constructor for UpperPriceLimit field
    constexpr explicit UpperPriceLimit(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of UpperPriceLimit field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of UpperPriceLimit field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
