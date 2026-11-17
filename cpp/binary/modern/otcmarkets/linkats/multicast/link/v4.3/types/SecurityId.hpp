// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/SecurityId.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Unique security ID issued by OTC Markets.
struct SecurityId {

    static constexpr const char* name = "Security Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SecurityId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of SecurityId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
