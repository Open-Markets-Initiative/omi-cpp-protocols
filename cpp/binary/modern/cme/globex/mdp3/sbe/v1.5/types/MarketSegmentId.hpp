#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v5 {


// Last Security update action on Incremental feed, 'D' or 'M' is used when a mid-week deletion or modification (i.e. extension) occurs
struct MarketSegmentId {

    static constexpr auto name = "Market Segment Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MarketSegmentId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketSegmentId(const std::uint8_t &value)
     : value{ value } {}

    // get value of MarketSegmentId field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
