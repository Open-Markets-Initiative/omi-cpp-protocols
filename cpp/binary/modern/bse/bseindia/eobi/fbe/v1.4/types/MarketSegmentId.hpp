#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Product identifier
struct MarketSegmentId {

    static constexpr const char* name = "Market Segment Id";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr MarketSegmentId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketSegmentId(const std::int32_t value)
     : value{ value } {}

    // get value of MarketSegmentId field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
