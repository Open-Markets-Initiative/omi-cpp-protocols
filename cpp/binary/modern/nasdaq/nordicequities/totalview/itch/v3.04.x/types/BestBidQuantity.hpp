#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Bid volume at top of book
struct BestBidQuantity {

    static constexpr const char* name = "Best Bid Quantity";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr BestBidQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BestBidQuantity(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of BestBidQuantity field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
