// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/SymbolLength.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// Symbol of the class
struct SymbolLength {

    static constexpr auto name = "Symbol Length";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SymbolLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SymbolLength(const std::uint8_t &value)
     : value{ value } {}

    // get value of SymbolLength field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
