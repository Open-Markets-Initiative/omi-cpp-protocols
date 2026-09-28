#pragma once

#include <array>
#include <cstddef>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {


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
