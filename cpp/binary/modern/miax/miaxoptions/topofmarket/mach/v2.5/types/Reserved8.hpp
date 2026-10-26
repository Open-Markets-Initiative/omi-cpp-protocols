#pragma once

#include <array>
#include <cstddef>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {


// Reserved for future use
struct Reserved8 {

    static constexpr auto name = "Reserved 8";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved8()
     : value{} {}

  protected:
    type value;
};
}
