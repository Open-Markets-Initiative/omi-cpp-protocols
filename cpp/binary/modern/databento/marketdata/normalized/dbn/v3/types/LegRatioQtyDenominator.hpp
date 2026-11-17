// Databento.MarketData.Normalized.Dbn.v3: types/LegRatioQtyDenominator.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The leg ratio qty denominator
struct LegRatioQtyDenominator {

    static constexpr const char* name = "Leg Ratio Qty Denominator";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr LegRatioQtyDenominator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegRatioQtyDenominator(const std::int32_t value)
     : value{ value } {}

    // get value of LegRatioQtyDenominator field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
