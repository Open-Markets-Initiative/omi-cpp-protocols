#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {


// tradingSessionSubID
struct TradingSessionSubId {

    static constexpr auto name = "Trading Session Sub Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr TradingSessionSubId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradingSessionSubId(const std::uint8_t &value)
     : value{ value } {}

    // get value of TradingSessionSubId field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
