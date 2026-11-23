// Eurex.T7.Eobi.Fbe.v6.0: types/Pad1.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v6_0 {


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
