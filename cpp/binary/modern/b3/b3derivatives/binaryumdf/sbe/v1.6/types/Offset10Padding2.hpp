// B3.B3Derivatives.BinaryUmdf.Sbe.v1.6: types/Offset10Padding2.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {


// 2 bytes padding
struct Offset10Padding2 {

    static constexpr auto name = "Offset 10 Padding 2";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Offset10Padding2()
     : value{} {}

  protected:
    type value;
};
}
