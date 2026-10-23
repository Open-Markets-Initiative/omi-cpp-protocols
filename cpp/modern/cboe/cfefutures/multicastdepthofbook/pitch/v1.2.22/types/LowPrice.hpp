#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// The lower of lowest offer price and lowest trade price for the day. Block and ECRP trades (Trade Condition=B or E) do not update Low Price.
struct LowPrice {

    static constexpr const char* name = "Low Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr LowPrice()
     : value{ 0 } {}

    // constructor for LowPrice field
    constexpr explicit LowPrice(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of LowPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of LowPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
