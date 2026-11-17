// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/Size.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Number of shares.
struct Size {

    static constexpr const char* name = "Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Size()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Size(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of Size field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
