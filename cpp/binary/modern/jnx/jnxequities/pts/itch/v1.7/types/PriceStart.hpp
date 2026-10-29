#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::itch::v1_7 {

// Start of price range for this price tick size.
struct PriceStart {

    static constexpr const char* name = "Price Start";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 1;
    static constexpr double denominator = 10;
    using type = std::uint32_t;

    // default constructor
    constexpr PriceStart()
     : value{ 0 } {}

    // constructor for PriceStart field
    constexpr explicit PriceStart(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of PriceStart field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of PriceStart field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
