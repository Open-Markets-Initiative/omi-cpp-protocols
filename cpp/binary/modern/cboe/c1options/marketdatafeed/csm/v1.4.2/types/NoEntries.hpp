// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/NoEntries.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// Number of MDEntries in this message. Will not exceed 255
struct NoEntries {

    static constexpr auto name = "No Entries";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr NoEntries()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NoEntries(const std::uint8_t &value)
     : value{ value } {}

    // get value of NoEntries field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
