#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Open Interest for this symbol.
struct OpenInterest {

    static constexpr const char* name = "Open Interest";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OpenInterest()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OpenInterest(const std::uint32_t value)
     : value{ value } {}

    // get value of OpenInterest field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
