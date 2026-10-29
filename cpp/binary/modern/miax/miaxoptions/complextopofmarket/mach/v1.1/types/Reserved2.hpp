#pragma once

#include <array>
#include <cstddef>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {


// Reserved for future use
struct Reserved2 {

    static constexpr auto name = "Reserved 2";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved2()
     : value{} {}

  protected:
    type value;
};
}
