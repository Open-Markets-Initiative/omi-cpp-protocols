#pragma once

#include <array>
#include <cstddef>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {


// Reserved for future use.
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
