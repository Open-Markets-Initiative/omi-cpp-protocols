#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// For Pillar-powered markets, the total imbalance quantity at the Indicative Match Price. For NYSE, the total imbalance quantity at the Reference Price, truncated to the round lot.
struct TotalImbalanceQty {

    static constexpr const char* name = "Total Imbalance Qty";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TotalImbalanceQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TotalImbalanceQty(const std::uint32_t value)
     : value{ value } {}

    // get value of TotalImbalanceQty field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
