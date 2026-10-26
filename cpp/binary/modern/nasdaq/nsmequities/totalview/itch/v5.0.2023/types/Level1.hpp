#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Denotes the MWCB Level 1 Value.
struct Level1 {

    static constexpr const char* name = "Level 1";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::uint64_t;

    // default constructor
    constexpr Level1()
     : value{ 0 } {}

    // constructor for Level1 field
    constexpr explicit Level1(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of Level1 field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of Level1 field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
