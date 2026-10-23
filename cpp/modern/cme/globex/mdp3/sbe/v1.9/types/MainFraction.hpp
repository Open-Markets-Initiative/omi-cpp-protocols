#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {


// Price Denominator of Main Fraction
struct MainFraction {

    static constexpr auto name = "Main Fraction";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr MainFraction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MainFraction(const std::uint8_t &value)
     : value{ value } {}

    // get value of MainFraction field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
