#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Denotes the MWCB Level 2 Value.
struct Level2 {

    static constexpr const char* name = "Level 2";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::uint64_t;

    // default constructor
    constexpr Level2()
     : value{ 0 } {}

    // constructor for Level2 field
    constexpr explicit Level2(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of Level2 field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of Level2 field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
