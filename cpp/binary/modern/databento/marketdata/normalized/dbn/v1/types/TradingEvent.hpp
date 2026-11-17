// Databento.MarketData.Normalized.Dbn.v1: types/TradingEvent.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// Further information about a status update
struct TradingEvent {

    static constexpr const char* name = "Trading Event";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr TradingEvent()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradingEvent(const std::uint16_t value)
     : value{ value } {}

    // get value of TradingEvent field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
