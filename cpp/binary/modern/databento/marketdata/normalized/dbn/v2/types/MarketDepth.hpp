#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {

// The market depth
struct MarketDepth {

    static constexpr const char* name = "Market Depth";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr MarketDepth()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketDepth(const std::int32_t value)
     : value{ value } {}

    // get value of MarketDepth field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
