#pragma once

#include <array>
#include <cstddef>

namespace cboe::c1options::complex::pitch::v2_1_18 {


// Reserved
struct Padding {

    static constexpr auto name = "Padding";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Padding()
     : value{} {}

  protected:
    type value;
};
}
