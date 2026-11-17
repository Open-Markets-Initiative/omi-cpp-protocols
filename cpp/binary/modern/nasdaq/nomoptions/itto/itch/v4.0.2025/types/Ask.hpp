// Nasdaq.NomOptions.Itto.Itch.v4.0.2025: types/Ask.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The display ask price of the new quote.
struct Ask {

    static constexpr const char* name = "Ask";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr Ask()
     : value{ 0 } {}

    // constructor for Ask field
    constexpr explicit Ask(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of Ask field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of Ask field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
