#pragma once

#include <array>
#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// 2 bytes padding
struct Offset54Padding2 {

    static constexpr auto name = "Offset 54 Padding 2";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Offset54Padding2()
     : value{} {}

  protected:
    type value;
};
}
