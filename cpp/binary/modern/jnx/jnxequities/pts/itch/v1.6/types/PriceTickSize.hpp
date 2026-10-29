#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::itch::v1_6 {

// Price tick size.
struct PriceTickSize {

    static constexpr const char* name = "Price Tick Size";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 1;
    static constexpr double denominator = 10;
    using type = std::uint32_t;

    // default constructor
    constexpr PriceTickSize()
     : value{ 0 } {}

    // constructor for PriceTickSize field
    constexpr explicit PriceTickSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of PriceTickSize field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of PriceTickSize field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
