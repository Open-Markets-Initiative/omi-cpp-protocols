// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/UnderlyingSymbolLength.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// The underlying symbol
struct UnderlyingSymbolLength {

    static constexpr auto name = "Underlying Symbol Length";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr UnderlyingSymbolLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingSymbolLength(const std::uint8_t &value)
     : value{ value } {}

    // get value of UnderlyingSymbolLength field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
