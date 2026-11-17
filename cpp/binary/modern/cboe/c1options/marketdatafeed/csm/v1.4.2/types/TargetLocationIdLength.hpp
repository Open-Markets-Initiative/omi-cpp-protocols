// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/TargetLocationIdLength.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// 
struct TargetLocationIdLength {

    static constexpr auto name = "Target Location Id Length";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr TargetLocationIdLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TargetLocationIdLength(const std::uint8_t &value)
     : value{ value } {}

    // get value of TargetLocationIdLength field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
