// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/QuoteId.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Unique Quote ID.
struct QuoteId {

    static constexpr const char* name = "Quote Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr QuoteId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit QuoteId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of QuoteId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
