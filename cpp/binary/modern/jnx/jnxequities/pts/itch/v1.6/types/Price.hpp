#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::itch::v1_6 {

// Price of the order; for a reference price message, a value of 214,748,364.7 (7FFFFFFF hex) denotes no reference price available.
struct Price {

    static constexpr const char* name = "Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 1;
    static constexpr double denominator = 10;
    using type = std::uint32_t;

    // default constructor
    constexpr Price()
     : value{ 0 } {}

    // constructor for Price field
    constexpr explicit Price(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of Price field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of Price field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
