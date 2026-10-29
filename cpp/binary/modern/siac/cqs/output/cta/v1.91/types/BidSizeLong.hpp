#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v1_91 {

// The Bid Size identifies the number of round-lots, for a security
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
