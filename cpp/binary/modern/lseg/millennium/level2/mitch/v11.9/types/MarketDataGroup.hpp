#pragma once

#include <cstddef>

namespace lseg::millennium::level2::mitch::v11_9 {


// Identity of the market data group the payload messages relate to
struct MarketDataGroup {

    static constexpr auto name = "Market Data Group";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MarketDataGroup()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketDataGroup(const char &value)
     : value{ value } {}

    // get value of MarketDataGroup field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
