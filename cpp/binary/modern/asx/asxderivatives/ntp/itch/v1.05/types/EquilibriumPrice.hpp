#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Price at which matching will occur.
struct EquilibriumPrice {

    static constexpr const char* name = "Equilibrium Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::int64_t;

    // default constructor
    constexpr EquilibriumPrice()
     : value{ 0 } {}

    // constructor for EquilibriumPrice field
    constexpr explicit EquilibriumPrice(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of EquilibriumPrice field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of EquilibriumPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
