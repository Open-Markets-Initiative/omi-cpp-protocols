#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Leg ratio for the specified instrument
struct LegRatioAndSide {

    static constexpr const char* name = "Leg Ratio And Side";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr LegRatioAndSide()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegRatioAndSide(const std::int32_t value)
     : value{ value } {}

    // get value of LegRatioAndSide field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
