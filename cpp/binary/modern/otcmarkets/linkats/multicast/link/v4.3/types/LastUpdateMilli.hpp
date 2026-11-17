// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/LastUpdateMilli.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Milliseconds from UTC epoch.
struct LastUpdateMilli {

    static constexpr const char* name = "Last Update Milli";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr LastUpdateMilli()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LastUpdateMilli(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of LastUpdateMilli field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
