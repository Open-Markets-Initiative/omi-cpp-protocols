// Cme.Globex.Mdp3.Sbe.v1.9: types/LowLimitPriceEx.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {

// Lower price threshold for the instrument
struct LowLimitPriceEx {

    static constexpr const char* name = "Low Limit Price Ex";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor: the null the model states, where it states one
    constexpr LowLimitPriceEx()
     : value{ no_value } {}

    // constructor for LowLimitPriceEx field
    constexpr explicit LowLimitPriceEx(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of LowLimitPriceEx field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of LowLimitPriceEx field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
