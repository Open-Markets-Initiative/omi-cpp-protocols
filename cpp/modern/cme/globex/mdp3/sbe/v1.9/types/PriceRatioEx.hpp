#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {

// Used for price calculation in spread and leg pricing
struct PriceRatioEx {

    static constexpr const char* name = "Price Ratio Ex";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor
    constexpr PriceRatioEx()
     : value{ 0 } {}

    // constructor for PriceRatioEx field
    constexpr explicit PriceRatioEx(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of PriceRatioEx field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of PriceRatioEx field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
