#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// SOQ lower strike price.
struct LowerStrikePrice {

    static constexpr const char* name = "Lower Strike Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr LowerStrikePrice()
     : value{ 0 } {}

    // constructor for LowerStrikePrice field
    constexpr explicit LowerStrikePrice(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of LowerStrikePrice field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of LowerStrikePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
