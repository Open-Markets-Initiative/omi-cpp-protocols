#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// tradeDate
struct TradeDateOptional {

    static constexpr const char* name = "Trade Date Optional";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 0;

    // default constructor
    constexpr TradeDateOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeDateOptional(const std::uint16_t value)
     : value{ value } {}

    // get value of TradeDateOptional field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
