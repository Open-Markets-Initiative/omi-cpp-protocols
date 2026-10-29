#pragma once

#include <array>
#include <cstddef>

namespace eurex::t7::eobi::fbe::v6_0 {


// 
struct Pad7 {

    static constexpr auto name = "Pad7";
    static constexpr std::size_t size = 7;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Pad7()
     : value{} {}

  protected:
    type value;
};
}
