// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/TradeConditionLength.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// 
struct TradeConditionLength {

    static constexpr auto name = "Trade Condition Length";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr TradeConditionLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeConditionLength(const std::uint8_t &value)
     : value{ value } {}

    // get value of TradeConditionLength field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
