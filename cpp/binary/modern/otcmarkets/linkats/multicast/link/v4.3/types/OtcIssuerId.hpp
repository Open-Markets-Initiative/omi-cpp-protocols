// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/OtcIssuerId.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Unique issuer ID.
struct OtcIssuerId {

    static constexpr const char* name = "Otc Issuer Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OtcIssuerId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OtcIssuerId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of OtcIssuerId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
