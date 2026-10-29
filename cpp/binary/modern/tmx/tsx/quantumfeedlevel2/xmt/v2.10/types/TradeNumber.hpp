#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// A Unique Identifier Per Stock Assigned To Each Trade
struct TradeNumber {

    static constexpr const char* name = "Trade Number";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor
    constexpr TradeNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeNumber(const std::uint32_t value)
     : value{ value } {}

    // get value of TradeNumber field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
