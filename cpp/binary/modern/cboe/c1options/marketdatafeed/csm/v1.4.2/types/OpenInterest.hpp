// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/OpenInterest.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Open Interest
struct OpenInterest {

    static constexpr const char* name = "Open Interest";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OpenInterest()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OpenInterest(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of OpenInterest field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
