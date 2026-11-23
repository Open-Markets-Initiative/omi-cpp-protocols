// B3.B3Derivatives.BinaryUmdf.Sbe.v2.1: types/Offset3Padding5.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {


// 5 bytes padding
struct Offset3Padding5 {

    static constexpr auto name = "Offset 3 Padding 5";
    static constexpr std::size_t size = 5;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Offset3Padding5()
     : value{} {}

  protected:
    type value;
};
}
