// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/EopType.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// 
struct EopType {

    static constexpr auto name = "Eop Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr EopType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EopType(const std::uint8_t &value)
     : value{ value } {}

    // get value of EopType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
