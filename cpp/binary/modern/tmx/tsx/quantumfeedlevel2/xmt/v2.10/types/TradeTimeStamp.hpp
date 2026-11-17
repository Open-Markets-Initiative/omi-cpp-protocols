// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: types/TradeTimeStamp.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// The Time At Which The Trade Occurred Manually Set When A Trade Is Added
struct TradeTimeStamp {

    static constexpr const char* name = "Trade Time Stamp";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr TradeTimeStamp()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit TradeTimeStamp(const std::uint32_t value)
     : value{ value } {}

    // get value of TradeTimeStamp field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
