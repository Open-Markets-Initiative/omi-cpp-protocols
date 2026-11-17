// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/ReferencePriceId.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Unique Reference Price ID.
struct ReferencePriceId {

    static constexpr const char* name = "Reference Price Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ReferencePriceId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ReferencePriceId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of ReferencePriceId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
