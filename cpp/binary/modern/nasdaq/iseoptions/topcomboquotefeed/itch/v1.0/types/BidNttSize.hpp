#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Limit Bid size that can’t be traded through.
struct BidNttSize {

    static constexpr const char* name = "Bid Ntt Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BidNttSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidNttSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of BidNttSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
