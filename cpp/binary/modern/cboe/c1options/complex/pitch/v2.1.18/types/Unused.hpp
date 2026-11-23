// Cboe.C1Options.Complex.Pitch.v2.1.18: types/Unused.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace cboe::c1options::complex::pitch::v2_1_18 {


// Reserved
struct Unused {

    static constexpr auto name = "Unused";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Unused()
     : value{} {}

  protected:
    type value;
};
}
