#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Leg ratio (positive for buy, negative for sell).
struct LegRatio {

    static constexpr const char* name = "Leg Ratio";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr LegRatio()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegRatio(const std::int32_t value)
     : value{ value } {}

    // get value of LegRatio field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
