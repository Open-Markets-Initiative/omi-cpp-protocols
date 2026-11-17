// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/LegalMarket.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// 
struct LegalMarket {

    static constexpr auto name = "Legal Market";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr LegalMarket()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegalMarket(const std::uint8_t &value)
     : value{ value } {}

    // get value of LegalMarket field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
