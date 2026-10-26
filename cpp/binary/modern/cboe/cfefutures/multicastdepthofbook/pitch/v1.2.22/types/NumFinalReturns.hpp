#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Number of S&P 500 Index returns used in the Final Settlement Value calculation.
struct NumFinalReturns {

    static constexpr const char* name = "Num Final Returns";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr NumFinalReturns()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumFinalReturns(const std::uint16_t value)
     : value{ value } {}

    // get value of NumFinalReturns field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
