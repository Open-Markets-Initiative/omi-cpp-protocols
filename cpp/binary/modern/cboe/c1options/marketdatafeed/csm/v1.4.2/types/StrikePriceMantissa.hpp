// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/StrikePriceMantissa.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// First byte is the exponent, last 4 bytes are the mantissa. This field is required for options
struct StrikePriceMantissa {

    static constexpr const char* name = "Strike Price Mantissa";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr StrikePriceMantissa()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StrikePriceMantissa(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get value of StrikePriceMantissa field
    [[nodiscard]] std::int32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::int32_t value;
};
}
