// Cboe.C1Options.Complex.Pitch.v2.1.18: types/Reserved1.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace cboe::c1options::complex::pitch::v2_1_18 {


// Reserved
struct Reserved1 {

    static constexpr auto name = "Reserved 1";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved1()
     : value{} {}

  protected:
    type value;
};
}
