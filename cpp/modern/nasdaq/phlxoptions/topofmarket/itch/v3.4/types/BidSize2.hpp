#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// Aggregated number of contracts on the bid side being displayed in the options market at the current time.
struct BidSize2 {

    static constexpr const char* name = "Bid Size 2";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr BidSize2()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidSize2(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of BidSize2 field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
