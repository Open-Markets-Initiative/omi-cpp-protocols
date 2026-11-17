// Nasdaq.NomOptions.Itto.Itch.v4.0.2025: types/Bid.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The display bid price of the new quote.
struct Bid {

    static constexpr const char* name = "Bid";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr Bid()
     : value{ 0 } {}

    // constructor for Bid field
    constexpr explicit Bid(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of Bid field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of Bid field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
