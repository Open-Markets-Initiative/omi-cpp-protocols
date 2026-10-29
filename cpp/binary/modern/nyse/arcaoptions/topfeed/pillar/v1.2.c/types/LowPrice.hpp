#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// The Lowest price of the series for the day. Use the Price scale from the series mapping index.
struct LowPrice {

    static constexpr const char* name = "Low Price";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr LowPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LowPrice(const std::int32_t value)
     : value{ value } {}

    // get value of LowPrice field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
