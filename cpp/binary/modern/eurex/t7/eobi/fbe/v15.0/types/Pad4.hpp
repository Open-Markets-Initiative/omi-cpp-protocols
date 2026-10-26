#pragma once

#include <array>
#include <cstddef>

namespace eurex::t7::eobi::fbe::v15_0 {


// 
struct Pad4 {

    static constexpr auto name = "Pad4";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Pad4()
     : value{} {}

  protected:
    type value;
};
}
