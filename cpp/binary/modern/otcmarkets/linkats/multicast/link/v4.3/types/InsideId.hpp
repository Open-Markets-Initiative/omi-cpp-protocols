// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/InsideId.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Unique Inside ID.
struct InsideId {

    static constexpr const char* name = "Inside Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr InsideId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit InsideId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of InsideId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
