#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

// For Pillar-powered markets, the number of shares paired off at the Indicative Match Price. For NYSE, the number of shares paired off at the Reference Price, truncated to the nearest round lot quantity.
struct PairedQty {

    static constexpr const char* name = "Paired Qty";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr PairedQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PairedQty(const std::uint32_t value)
     : value{ value } {}

    // get value of PairedQty field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
