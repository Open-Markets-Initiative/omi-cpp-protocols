#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// The Highest price of the series for the day. Use the Price scale from the series index mapping.
struct HighPrice {

    static constexpr const char* name = "High Price";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr HighPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit HighPrice(const std::int32_t value)
     : value{ value } {}

    // get value of HighPrice field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
