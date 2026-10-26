#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {

// Monetary value equivalent to the minimum price fluctuation
struct MinPriceIncrementAmountEx {

    static constexpr const char* name = "Min Price Increment Amount Ex";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor
    constexpr MinPriceIncrementAmountEx()
     : value{ 0 } {}

    // constructor for MinPriceIncrementAmountEx field
    constexpr explicit MinPriceIncrementAmountEx(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MinPriceIncrementAmountEx field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of MinPriceIncrementAmountEx field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
