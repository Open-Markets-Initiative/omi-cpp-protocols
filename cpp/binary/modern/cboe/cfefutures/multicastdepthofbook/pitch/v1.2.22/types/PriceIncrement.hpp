#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Minimum Price Increment.
struct PriceIncrement {

    static constexpr const char* name = "Price Increment";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr PriceIncrement()
     : value{ 0 } {}

    // constructor for PriceIncrement field
    constexpr explicit PriceIncrement(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of PriceIncrement field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of PriceIncrement field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
