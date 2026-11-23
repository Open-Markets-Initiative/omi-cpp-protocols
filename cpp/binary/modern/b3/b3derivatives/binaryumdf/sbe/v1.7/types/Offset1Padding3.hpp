// B3.B3Derivatives.BinaryUmdf.Sbe.v1.7: types/Offset1Padding3.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {


// 3 bytes padding
struct Offset1Padding3 {

    static constexpr auto name = "Offset 1 Padding 3";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Offset1Padding3()
     : value{} {}

  protected:
    type value;
};
}
