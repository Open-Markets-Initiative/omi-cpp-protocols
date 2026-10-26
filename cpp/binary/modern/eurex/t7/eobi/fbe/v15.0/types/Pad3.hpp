#pragma once

#include <array>
#include <cstddef>

namespace eurex::t7::eobi::fbe::v15_0 {


// 
struct Pad3 {

    static constexpr auto name = "Pad3";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Pad3()
     : value{} {}

  protected:
    type value;
};
}
