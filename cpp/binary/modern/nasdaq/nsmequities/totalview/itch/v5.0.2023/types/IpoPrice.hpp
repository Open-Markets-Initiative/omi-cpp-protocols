#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Denotes the IPO price to be used for intraday net change calculations
struct IpoPrice {

    static constexpr const char* name = "Ipo Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr IpoPrice()
     : value{ 0 } {}

    // constructor for IpoPrice field
    constexpr explicit IpoPrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of IpoPrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of IpoPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
