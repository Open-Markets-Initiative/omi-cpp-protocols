#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Trade Date. Represented as number of days since 1 January 1970.
struct TradeDate {

    static constexpr const char* name = "Trade Date";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr TradeDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeDate(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of TradeDate field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
