#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The display bid price of the replaced quote.
struct BidPriceLong {

    static constexpr const char* name = "Bid Price Long";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr BidPriceLong()
     : value{ 0 } {}

    // constructor for BidPriceLong field
    constexpr explicit BidPriceLong(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of BidPriceLong field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of BidPriceLong field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
