// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/SecurityTypeLength.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// 
struct SecurityTypeLength {

    static constexpr auto name = "Security Type Length";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SecurityTypeLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityTypeLength(const std::uint8_t &value)
     : value{ value } {}

    // get value of SecurityTypeLength field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
