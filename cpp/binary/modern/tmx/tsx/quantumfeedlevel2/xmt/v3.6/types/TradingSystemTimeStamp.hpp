// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/TradingSystemTimeStamp.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {


// The Time At Which The Event Being Reported Occurred In The Trading Engine
struct TradingSystemTimeStamp {

    static constexpr auto name = "Trading System Time Stamp";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr TradingSystemTimeStamp()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradingSystemTimeStamp(const std::uint64_t &value)
     : value{ value } {}

    // get value of TradingSystemTimeStamp field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
