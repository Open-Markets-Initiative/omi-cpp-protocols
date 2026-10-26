#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Leg Ratio. This field will repeat for each leg.
struct LegRatioQty {

    static constexpr const char* name = "Leg Ratio Qty";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr LegRatioQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegRatioQty(const std::uint16_t value)
     : value{ value } {}

    // get value of LegRatioQty field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
