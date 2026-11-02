#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The leg ratio price denominator
struct LegRatioPriceDenominator {

    static constexpr const char* name = "Leg Ratio Price Denominator";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr LegRatioPriceDenominator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegRatioPriceDenominator(const std::int32_t value)
     : value{ value } {}

    // get value of LegRatioPriceDenominator field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
