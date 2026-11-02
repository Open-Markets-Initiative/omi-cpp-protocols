#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The market segment id
struct MarketSegmentId {

    static constexpr const char* name = "Market Segment Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MarketSegmentId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketSegmentId(const std::uint32_t value)
     : value{ value } {}

    // get value of MarketSegmentId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
