// Eurex.T7.Eobi.Fbe.v3.0: types/Pad3.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v3_0 {


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
