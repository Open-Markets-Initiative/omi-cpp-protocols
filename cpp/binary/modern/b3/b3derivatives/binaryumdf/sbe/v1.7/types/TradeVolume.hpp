#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// tradeVolume
struct TradeVolume {

    static constexpr const char* name = "Trade Volume";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;

    // default constructor
    constexpr TradeVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeVolume(const std::int64_t value)
     : value{ value } {}

    // get value of TradeVolume field
    [[nodiscard]] std::int64_t get() const {
        return value;
    }

  protected:
    std::int64_t value;
};
}
