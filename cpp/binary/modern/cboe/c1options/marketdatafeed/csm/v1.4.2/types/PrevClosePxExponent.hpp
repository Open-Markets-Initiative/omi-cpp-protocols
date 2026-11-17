// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/PrevClosePxExponent.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// Previous day’s close price for security.
struct PrevClosePxExponent {

    static constexpr auto name = "Prev Close Px Exponent";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;

    // default constructor
    constexpr PrevClosePxExponent()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PrevClosePxExponent(const std::int8_t &value)
     : value{ value } {}

    // get value of PrevClosePxExponent field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
