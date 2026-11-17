// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/LegRatioQty.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Leg ratio
struct LegRatioQty {

    static constexpr const char* name = "Leg Ratio Qty";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr LegRatioQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegRatioQty(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of LegRatioQty field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
