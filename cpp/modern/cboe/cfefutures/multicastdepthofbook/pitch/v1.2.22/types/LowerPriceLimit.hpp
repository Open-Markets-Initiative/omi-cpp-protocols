#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Lower price limit
struct LowerPriceLimit {

    static constexpr const char* name = "Lower Price Limit";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr LowerPriceLimit()
     : value{ 0 } {}

    // constructor for LowerPriceLimit field
    constexpr explicit LowerPriceLimit(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of LowerPriceLimit field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of LowerPriceLimit field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
