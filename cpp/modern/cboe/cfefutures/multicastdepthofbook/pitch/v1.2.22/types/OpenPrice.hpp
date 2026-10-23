#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// The first trade on the day (in any session) will set the Open Price for the day (valid only if Total Volume > 0). Block and ECRP trades (Trade Condition=B or E) do not update Open Price.
struct OpenPrice {

    static constexpr const char* name = "Open Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr OpenPrice()
     : value{ 0 } {}

    // constructor for OpenPrice field
    constexpr explicit OpenPrice(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of OpenPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of OpenPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
