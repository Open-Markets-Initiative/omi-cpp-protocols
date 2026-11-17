// Eurex.T7.Eobi.Fbe.v15.0: types/Pad2.hpp
#pragma once

#include <array>
#include <cstddef>

namespace eurex::t7::eobi::fbe::v15_0 {


// 
struct Pad2 {

    static constexpr auto name = "Pad2";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Pad2()
     : value{} {}

  protected:
    type value;
};
}
