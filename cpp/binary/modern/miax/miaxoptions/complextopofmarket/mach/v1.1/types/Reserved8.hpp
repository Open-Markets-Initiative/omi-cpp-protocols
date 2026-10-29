#pragma once

#include <array>
#include <cstddef>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {


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
