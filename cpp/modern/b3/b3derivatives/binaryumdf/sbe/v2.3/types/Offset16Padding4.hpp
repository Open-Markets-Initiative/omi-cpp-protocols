#pragma once

#include <array>
#include <cstddef>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {


// 4 bytes padding
struct Offset16Padding4 {

    static constexpr auto name = "Offset 16 Padding 4";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Offset16Padding4()
     : value{} {}

  protected:
    type value;
};
}
