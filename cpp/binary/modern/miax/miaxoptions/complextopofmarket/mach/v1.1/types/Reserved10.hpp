#pragma once

#include <array>
#include <cstddef>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {


// Reserved for future use **
struct Reserved10 {

    static constexpr auto name = "Reserved 10";
    static constexpr std::size_t size = 10;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved10()
     : value{} {}

  protected:
    type value;
};
}
