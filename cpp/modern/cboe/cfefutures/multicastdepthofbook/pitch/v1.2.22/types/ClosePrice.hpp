#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// The last trade on the day (in any session) will set the Close Price for the day (valid only if Total Volume > 0). Block and ECRP trades (Trade Condition=B or E) do not update Close Price.
struct ClosePrice {

    static constexpr const char* name = "Close Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr ClosePrice()
     : value{ 0 } {}

    // constructor for ClosePrice field
    constexpr explicit ClosePrice(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of ClosePrice field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of ClosePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
