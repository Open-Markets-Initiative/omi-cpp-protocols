#pragma once

#include <array>
#include <cstddef>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {


// 1 bytes padding
struct Padding1 {

    static constexpr auto name = "Padding 1";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Padding1()
     : value{} {}

  protected:
    type value;
};
}
