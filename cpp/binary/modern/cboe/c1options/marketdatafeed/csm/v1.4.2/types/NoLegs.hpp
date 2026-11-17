// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/NoLegs.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {


// Num. of Legs in a strategy product. Only used for products that contain legs such as strategies. Will not exceed 255.
struct NoLegs {

    static constexpr auto name = "No Legs";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr NoLegs()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NoLegs(const std::uint8_t &value)
     : value{ value } {}

    // get value of NoLegs field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
