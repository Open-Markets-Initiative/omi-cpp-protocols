#pragma once

#include <array>
#include <cstddef>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {


// 2 bytes padding
struct Offset34Padding2 {

    static constexpr auto name = "Offset 34 Padding 2";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Offset34Padding2()
     : value{} {}

  protected:
    type value;
};
}
