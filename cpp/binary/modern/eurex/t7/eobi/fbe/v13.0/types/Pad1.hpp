#pragma once

#include <array>
#include <cstddef>

namespace eurex::t7::eobi::fbe::v13_0 {


// 
struct Pad1 {

    static constexpr auto name = "Pad1";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Pad1()
     : value{} {}

  protected:
    type value;
};
}
