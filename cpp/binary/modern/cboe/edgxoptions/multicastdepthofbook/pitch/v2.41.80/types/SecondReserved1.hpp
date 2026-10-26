#pragma once

#include <array>
#include <cstddef>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {


// Reserved.
struct SecondReserved1 {

    static constexpr auto name = "Second Reserved 1";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr SecondReserved1()
     : value{} {}

  protected:
    type value;
};
}
