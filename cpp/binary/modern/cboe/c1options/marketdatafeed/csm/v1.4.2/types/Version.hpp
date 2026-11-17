// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/Version.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// The version associated with the contents and format of this header. Currently, this will be a constant value of 1.
struct Version {

    static constexpr auto name = "Version";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr Version()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Version(const std::uint8_t &value)
     : value{ value } {}

    // get value of Version field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
