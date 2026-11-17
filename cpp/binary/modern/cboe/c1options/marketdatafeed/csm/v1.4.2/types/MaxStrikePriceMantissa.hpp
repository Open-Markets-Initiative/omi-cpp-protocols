// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/MaxStrikePriceMantissa.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// The maximum allowable strike price.
struct MaxStrikePriceMantissa {

    static constexpr const char* name = "Max Strike Price Mantissa";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr MaxStrikePriceMantissa()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MaxStrikePriceMantissa(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get value of MaxStrikePriceMantissa field
    [[nodiscard]] std::int32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::int32_t value;
};
}
