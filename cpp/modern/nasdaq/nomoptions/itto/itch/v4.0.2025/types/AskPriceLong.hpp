#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The display ask price of the replaced quote.
struct AskPriceLong {

    static constexpr const char* name = "Ask Price Long";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr AskPriceLong()
     : value{ 0 } {}

    // constructor for AskPriceLong field
    constexpr explicit AskPriceLong(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of AskPriceLong field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of AskPriceLong field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
