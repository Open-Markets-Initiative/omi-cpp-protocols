#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The display price of the new order being added to the book.
struct PriceLong {

    static constexpr const char* name = "Price Long";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr PriceLong()
     : value{ 0 } {}

    // constructor for PriceLong field
    constexpr explicit PriceLong(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of PriceLong field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of PriceLong field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
