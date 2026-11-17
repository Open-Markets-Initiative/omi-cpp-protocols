// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/PriceType.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// Specifies how to interpret the value in the StrikePrice field.
struct PriceType {

    static constexpr auto name = "Price Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr PriceType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceType(const std::uint8_t &value)
     : value{ value } {}

    // get value of PriceType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
