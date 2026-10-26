#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// tradeDate
struct TradeDate {

    static constexpr const char* name = "Trade Date";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr TradeDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeDate(const std::uint16_t value)
     : value{ value } {}

    // get value of TradeDate field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
