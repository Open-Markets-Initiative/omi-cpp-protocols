#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// The higher of highest bid price and highest trade price for the day. Block and ECRP trades (Trade Condition=B or E) do not update High Price.
struct HighPrice {

    static constexpr const char* name = "High Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr HighPrice()
     : value{ 0 } {}

    // constructor for HighPrice field
    constexpr explicit HighPrice(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of HighPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of HighPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
