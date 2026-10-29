#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// Denotes the explicit strike price of the option. Refer to Data Types for field processing notes.
struct ExplicitStrikePrice {

    static constexpr const char* name = "Explicit Strike Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;

    // default constructor
    constexpr ExplicitStrikePrice()
     : value{ 0 } {}

    // constructor for ExplicitStrikePrice field
    constexpr explicit ExplicitStrikePrice(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of ExplicitStrikePrice field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of ExplicitStrikePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
