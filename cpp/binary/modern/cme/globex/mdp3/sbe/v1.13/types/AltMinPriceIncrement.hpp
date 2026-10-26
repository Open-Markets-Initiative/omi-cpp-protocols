#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// New sub-tick which is only available for order entry when certain conditions are met, tick value which corresponds to the Alt Min Quote Life
struct AltMinPriceIncrement {

    static constexpr const char* name = "Alt Min Price Increment";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor
    constexpr AltMinPriceIncrement()
     : value{ 0 } {}

    // constructor for AltMinPriceIncrement field
    constexpr explicit AltMinPriceIncrement(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of AltMinPriceIncrement field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of AltMinPriceIncrement field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
