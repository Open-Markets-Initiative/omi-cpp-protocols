// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/EopExponent.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// The expected opening price
struct EopExponent {

    static constexpr auto name = "Eop Exponent";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;

    // default constructor
    constexpr EopExponent()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EopExponent(const std::int8_t &value)
     : value{ value } {}

    // get value of EopExponent field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
