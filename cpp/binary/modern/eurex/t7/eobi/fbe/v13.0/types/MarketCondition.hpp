#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v13_0 {


// 
struct MarketCondition {

    static constexpr auto name = "Market Condition";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0xFF;
static const type maximum_value = 1;
static const type minimum_value = 0;

    // default constructor
    constexpr MarketCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketCondition(const std::uint8_t &value)
     : value{ value } {}

    // get value of MarketCondition field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
