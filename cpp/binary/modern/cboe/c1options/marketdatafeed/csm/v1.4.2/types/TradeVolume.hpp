// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/TradeVolume.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Total trade volume for security
struct TradeVolume {

    static constexpr const char* name = "Trade Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TradeVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeVolume(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of TradeVolume field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
