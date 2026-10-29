#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::bbo::xdp::v2_4_g {


// Trading session value
struct TradingSession {

    static constexpr auto name = "Trading Session";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr TradingSession()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradingSession(const std::uint8_t &value)
     : value{ value } {}

    // get value of TradingSession field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
