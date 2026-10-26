#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v8 {


// Price Denominator of Sub Fraction
struct SubFraction {

    static constexpr auto name = "Sub Fraction";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr SubFraction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SubFraction(const std::uint8_t &value)
     : value{ value } {}

    // get value of SubFraction field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
