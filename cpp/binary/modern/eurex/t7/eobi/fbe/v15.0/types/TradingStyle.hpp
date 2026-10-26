#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v15_0 {


// 
struct TradingStyle {

    static constexpr auto name = "Trading Style";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0xFF;
static const type maximum_value = 4;
static const type minimum_value = 1;

    // default constructor
    constexpr TradingStyle()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradingStyle(const std::uint8_t &value)
     : value{ value } {}

    // get value of TradingStyle field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
