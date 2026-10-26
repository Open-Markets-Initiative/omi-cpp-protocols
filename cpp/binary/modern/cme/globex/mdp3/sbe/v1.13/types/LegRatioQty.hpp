#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {


// Leg ratio of quantity for this individual leg relative to the entire multi-leg instrument
struct LegRatioQty {

    static constexpr auto name = "Leg Ratio Qty";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;

    // default constructor
    constexpr LegRatioQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegRatioQty(const std::int8_t &value)
     : value{ value } {}

    // get value of LegRatioQty field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
