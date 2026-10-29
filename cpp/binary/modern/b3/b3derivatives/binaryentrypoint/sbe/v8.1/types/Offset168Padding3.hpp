#pragma once

#include <array>
#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// 3 bytes padding
struct Offset168Padding3 {

    static constexpr auto name = "Offset 168 Padding 3";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Offset168Padding3()
     : value{} {}

  protected:
    type value;
};
}
