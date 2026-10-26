#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v2_10_a {

// Identifies the number of shares for a symbol rounded down to the nearest multiple of its Round Lot Size
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
