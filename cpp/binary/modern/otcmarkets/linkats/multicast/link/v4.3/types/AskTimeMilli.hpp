// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/AskTimeMilli.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Ask timestamp in milliseconds from UTC epoch.
struct AskTimeMilli {

    static constexpr const char* name = "Ask Time Milli";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr AskTimeMilli()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskTimeMilli(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of AskTimeMilli field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
