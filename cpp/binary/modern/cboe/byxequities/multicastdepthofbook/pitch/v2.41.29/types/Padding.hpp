#pragma once

#include <array>
#include <cstddef>

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {


// Reserved
struct Padding {

    static constexpr auto name = "Padding";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Padding()
     : value{} {}

  protected:
    type value;
};
}
