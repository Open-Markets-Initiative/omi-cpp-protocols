// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: types/Reserved16.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {


// Reserved for future use
struct Reserved16 {

    static constexpr auto name = "Reserved 16";
    static constexpr std::size_t size = 16;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved16()
     : value{} {}

  protected:
    type value;
};
}
