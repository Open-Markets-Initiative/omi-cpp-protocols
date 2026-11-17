// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/MessageLength.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Length of the message in bytes
struct MessageLength {

    static constexpr const char* name = "Message Length";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr MessageLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MessageLength(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of MessageLength field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
