// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/PacketLength.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Length of the packet including this length field and the version
struct PacketLength {

    static constexpr const char* name = "Packet Length";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr PacketLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PacketLength(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of PacketLength field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
