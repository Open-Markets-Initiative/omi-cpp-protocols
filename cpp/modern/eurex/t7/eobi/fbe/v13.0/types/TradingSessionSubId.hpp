#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v13_0 {


// 
struct TradingSessionSubId {

    static constexpr auto name = "Trading Session Sub Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0xFF;
static const type maximum_value = 7;
static const type minimum_value = 1;

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
