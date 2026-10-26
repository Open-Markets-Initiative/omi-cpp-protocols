#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// Explicit strike price. Refer to Data Types for field processing notes.
struct ExplicitStrikePrice {

    static constexpr const char* name = "Explicit Strike Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr ExplicitStrikePrice()
     : value{ 0 } {}

    // constructor for ExplicitStrikePrice field
    constexpr explicit ExplicitStrikePrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of ExplicitStrikePrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of ExplicitStrikePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
