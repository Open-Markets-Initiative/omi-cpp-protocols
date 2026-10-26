#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v15_0 {

// 
struct TradeCondition {

    static constexpr const char* name = "Trade Condition";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 0xFFFF;
static const type maximum_value = 743;
static const type minimum_value = 1;

    // default constructor
    constexpr TradeCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeCondition(const std::uint16_t value)
     : value{ value } {}

    // get value of TradeCondition field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
