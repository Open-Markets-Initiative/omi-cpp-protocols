// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/NetChgPrevDayExponent.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// Net change of last sale price relative to previous close price. Sign of this value implies direction of change.
struct NetChgPrevDayExponent {

    static constexpr auto name = "Net Chg Prev Day Exponent";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;

    // default constructor
    constexpr NetChgPrevDayExponent()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NetChgPrevDayExponent(const std::int8_t &value)
     : value{ value } {}

    // get value of NetChgPrevDayExponent field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
