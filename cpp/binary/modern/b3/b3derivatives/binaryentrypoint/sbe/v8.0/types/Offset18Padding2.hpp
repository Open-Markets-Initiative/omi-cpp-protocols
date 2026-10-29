#pragma once

#include <array>
#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// 2 bytes padding
struct Offset18Padding2 {

    static constexpr auto name = "Offset 18 Padding 2";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Offset18Padding2()
     : value{} {}

  protected:
    type value;
};
}
