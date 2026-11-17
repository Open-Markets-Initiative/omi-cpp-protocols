// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/QuoteTimeMilli.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Quote timestamp in milliseconds from UTC epoch.
struct QuoteTimeMilli {

    static constexpr const char* name = "Quote Time Milli";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr QuoteTimeMilli()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit QuoteTimeMilli(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of QuoteTimeMilli field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
