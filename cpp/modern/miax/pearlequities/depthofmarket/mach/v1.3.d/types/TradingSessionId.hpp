#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {


// The current trading session ID of the corresponding Matching Engine
struct TradingSessionId {

    static constexpr auto name = "Trading Session Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr TradingSessionId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradingSessionId(const std::uint8_t &value)
     : value{ value } {}

    // get value of TradingSessionId field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
