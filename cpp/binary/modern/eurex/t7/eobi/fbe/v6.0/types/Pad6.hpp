// Eurex.T7.Eobi.Fbe.v6.0: types/Pad6.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v6_0 {


// 
struct Pad6 {

    static constexpr auto name = "Pad6";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Pad6()
     : value{} {}

  protected:
    type value;
};
}
