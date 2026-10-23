#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// Explicit strike price. Refer to Data Types for field processing notes.
struct StrikePrice {

    static constexpr const char* name = "Strike Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int32_t;

    // default constructor
    constexpr StrikePrice()
     : value{ 0 } {}

    // constructor for StrikePrice field
    constexpr explicit StrikePrice(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of StrikePrice field
    [[nodiscard]] std::int32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of StrikePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int32_t value;
};
}
