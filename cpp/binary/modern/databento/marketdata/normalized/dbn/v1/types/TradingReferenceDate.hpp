#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The trading session date corresponding to the settlement price in trading_reference_price, in number of days since the UNIX epoch
struct TradingReferenceDate {

    static constexpr const char* name = "Trading Reference Date";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr TradingReferenceDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradingReferenceDate(const std::uint16_t value)
     : value{ value } {}

    // get value of TradingReferenceDate field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
