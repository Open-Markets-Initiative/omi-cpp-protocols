#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g {

// The total market order imbalance quantity at the Reference Price.
struct MarketImbalanceQty {

    static constexpr const char* name = "Market Imbalance Qty";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MarketImbalanceQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketImbalanceQty(const std::uint32_t value)
     : value{ value } {}

    // get value of MarketImbalanceQty field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
