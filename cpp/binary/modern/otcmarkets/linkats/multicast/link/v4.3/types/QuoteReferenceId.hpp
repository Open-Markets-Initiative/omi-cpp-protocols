// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/QuoteReferenceId.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Numeric value (0–64,999) assigned by the quote owner (FIX Tag 9670), used for correlation purposes.
struct QuoteReferenceId {

    static constexpr const char* name = "Quote Reference Id";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr QuoteReferenceId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit QuoteReferenceId(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of QuoteReferenceId field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
