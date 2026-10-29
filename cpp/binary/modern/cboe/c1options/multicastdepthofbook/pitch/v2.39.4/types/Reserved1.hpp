#pragma once

#include <array>
#include <cstddef>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {


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
