#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// Indicates whether a synthetic match is occured.
struct TradeCondition {

    static constexpr auto name = "Trade Condition";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr TradeCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeCondition(const std::uint8_t &value)
     : value{ value } {}

    // get value of TradeCondition field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
