#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {

// The ratio of quantity for this individual leg relative to the entire multi-leg security.
struct LegRatioQty {

    static constexpr const char* name = "Leg Ratio Qty";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = -2147483648;

    // default constructor
    constexpr LegRatioQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegRatioQty(const std::int32_t value)
     : value{ value } {}

    // get value of LegRatioQty field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
