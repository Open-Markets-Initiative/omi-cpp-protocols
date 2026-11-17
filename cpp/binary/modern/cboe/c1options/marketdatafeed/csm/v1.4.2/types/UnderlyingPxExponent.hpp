// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/UnderlyingPxExponent.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// Price of underlying security
struct UnderlyingPxExponent {

    static constexpr auto name = "Underlying Px Exponent";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;

    // default constructor
    constexpr UnderlyingPxExponent()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingPxExponent(const std::int8_t &value)
     : value{ value } {}

    // get value of UnderlyingPxExponent field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
