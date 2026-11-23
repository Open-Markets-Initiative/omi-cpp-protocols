// Eurex.T7.Eobi.Fbe.v15.0: types/Pad5.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v15_0 {


// 
struct Pad5 {

    static constexpr auto name = "Pad5";
    static constexpr std::size_t size = 5;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Pad5()
     : value{} {}

  protected:
    type value;
};
}
