#pragma once

#include <array>
#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// 3 bytes padding
struct Offset146Padding3 {

    static constexpr auto name = "Offset 146 Padding 3";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Offset146Padding3()
     : value{} {}

  protected:
    type value;
};
}
