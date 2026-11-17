// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/AskSize.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Number of shares on the ask.
struct AskSize {

    static constexpr const char* name = "Ask Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr AskSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of AskSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
