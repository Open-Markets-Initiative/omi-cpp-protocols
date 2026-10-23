#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Equilibrium price if the order book is crossed
struct EquilibriumPrice {

    static constexpr const char* name = "Equilibrium Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr EquilibriumPrice()
     : value{ 0 } {}

    // constructor for EquilibriumPrice field
    constexpr explicit EquilibriumPrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of EquilibriumPrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of EquilibriumPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
