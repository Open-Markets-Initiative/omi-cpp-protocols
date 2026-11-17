// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/SendingTime.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// The time that this packet was sent. It applies to all messages in this packet.
struct SendingTime {

    static constexpr const char* name = "Sending Time";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr SendingTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SendingTime(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of SendingTime field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
