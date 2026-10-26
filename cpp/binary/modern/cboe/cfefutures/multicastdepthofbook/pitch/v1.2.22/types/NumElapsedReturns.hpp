#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Number of elapsed S&P 500 Index returns including the current day.
struct NumElapsedReturns {

    static constexpr const char* name = "Num Elapsed Returns";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr NumElapsedReturns()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumElapsedReturns(const std::uint16_t value)
     : value{ value } {}

    // get value of NumElapsedReturns field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
