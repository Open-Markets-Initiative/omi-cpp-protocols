// Databento.MarketData.Normalized.Dbn.v3: types/LegRatioQtyNumerator.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The leg ratio qty numerator
struct LegRatioQtyNumerator {

    static constexpr const char* name = "Leg Ratio Qty Numerator";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr LegRatioQtyNumerator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegRatioQtyNumerator(const std::int32_t value)
     : value{ value } {}

    // get value of LegRatioQtyNumerator field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
