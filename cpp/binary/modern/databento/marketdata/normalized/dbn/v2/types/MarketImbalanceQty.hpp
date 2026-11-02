#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {

// Reserved for future use
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
