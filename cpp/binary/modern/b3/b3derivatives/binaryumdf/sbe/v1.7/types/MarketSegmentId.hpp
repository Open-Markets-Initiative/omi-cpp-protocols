#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {


// marketSegmentID
struct MarketSegmentId {

    static constexpr auto name = "Market Segment Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0;

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
