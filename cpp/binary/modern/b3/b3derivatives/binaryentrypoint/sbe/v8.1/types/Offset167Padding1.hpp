#pragma once

#include <array>
#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// 1 bytes padding
struct Offset167Padding1 {

    static constexpr auto name = "Offset 167 Padding 1";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Offset167Padding1()
     : value{} {}

  protected:
    type value;
};
}
