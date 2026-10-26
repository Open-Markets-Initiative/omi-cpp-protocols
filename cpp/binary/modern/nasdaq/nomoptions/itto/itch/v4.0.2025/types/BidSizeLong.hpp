#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The bid contracts of the new quote.
struct BidSizeLong {

    static constexpr const char* name = "Bid Size Long";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BidSizeLong()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidSizeLong(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of BidSizeLong field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
