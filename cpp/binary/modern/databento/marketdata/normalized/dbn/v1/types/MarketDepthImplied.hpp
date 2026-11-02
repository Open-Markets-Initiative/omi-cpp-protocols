#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The market depth implied
struct MarketDepthImplied {

    static constexpr const char* name = "Market Depth Implied";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr MarketDepthImplied()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketDepthImplied(const std::int32_t value)
     : value{ value } {}

    // get value of MarketDepthImplied field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
