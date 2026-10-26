#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {

// Differential value for price banding
struct MaxPriceVariationEx {

    static constexpr const char* name = "Max Price Variation Ex";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor
    constexpr MaxPriceVariationEx()
     : value{ 0 } {}

    // constructor for MaxPriceVariationEx field
    constexpr explicit MaxPriceVariationEx(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MaxPriceVariationEx field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of MaxPriceVariationEx field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
