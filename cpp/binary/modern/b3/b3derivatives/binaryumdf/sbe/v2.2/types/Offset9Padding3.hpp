#pragma once

#include <array>
#include <cstddef>

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {


// 3 bytes padding
struct Offset9Padding3 {

    static constexpr auto name = "Offset 9 Padding 3";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Offset9Padding3()
     : value{} {}

  protected:
    type value;
};
}
