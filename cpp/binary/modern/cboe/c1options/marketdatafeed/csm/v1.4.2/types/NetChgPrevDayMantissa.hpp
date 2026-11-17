// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/NetChgPrevDayMantissa.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Net change of last sale price relative to previous close price. Sign of this value implies direction of change.
struct NetChgPrevDayMantissa {

    static constexpr const char* name = "Net Chg Prev Day Mantissa";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr NetChgPrevDayMantissa()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NetChgPrevDayMantissa(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get value of NetChgPrevDayMantissa field
    [[nodiscard]] std::int32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::int32_t value;
};
}
