// Cme.Globex.Mdp3.Sbe.v1.13: types/MinPriceIncrementOptionalEx.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Minimum constant tick for the instrument
struct MinPriceIncrementOptionalEx {

    static constexpr const char* name = "Min Price Increment Optional Ex";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor: the null the model states, where it states one
    constexpr MinPriceIncrementOptionalEx()
     : value{ no_value } {}

    // constructor for MinPriceIncrementOptionalEx field
    constexpr explicit MinPriceIncrementOptionalEx(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MinPriceIncrementOptionalEx field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of MinPriceIncrementOptionalEx field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
