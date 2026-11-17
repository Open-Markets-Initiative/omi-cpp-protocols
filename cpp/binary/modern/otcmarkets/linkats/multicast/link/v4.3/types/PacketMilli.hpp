// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/PacketMilli.hpp
#pragma once

#include <bit>
#include <chrono>
#include <cstddef>
#include <cstdint>

#include "../common/Day.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Milliseconds since local time midnight (EST/EDT)
struct PacketMilli {

    static constexpr const char* name = "Packet Milli";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr PacketMilli()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PacketMilli(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of PacketMilli field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

    // PacketMilli on a day: its milliseconds since midnight, America/New_York, as UTC Unix nanoseconds
    [[nodiscard]] std::int64_t utc(const calendar::Day& day) const {
        return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(get()) * 1000000);
    }

  protected:
    std::uint32_t value;
};
}
