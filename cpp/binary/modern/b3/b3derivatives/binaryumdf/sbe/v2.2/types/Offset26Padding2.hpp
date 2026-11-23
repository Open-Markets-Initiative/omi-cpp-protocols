// B3.B3Derivatives.BinaryUmdf.Sbe.v2.2: types/Offset26Padding2.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {


// 2 bytes padding
struct Offset26Padding2 {

    static constexpr auto name = "Offset 26 Padding 2";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Offset26Padding2()
     : value{} {}

  protected:
    type value;
};
}
