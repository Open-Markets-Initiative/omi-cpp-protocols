#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Upper price limit
struct UpperPriceLimit {

    static constexpr const char* name = "Upper Price Limit";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr UpperPriceLimit()
     : value{ 0 } {}

    // constructor for UpperPriceLimit field
    constexpr explicit UpperPriceLimit(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of UpperPriceLimit field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of UpperPriceLimit field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
