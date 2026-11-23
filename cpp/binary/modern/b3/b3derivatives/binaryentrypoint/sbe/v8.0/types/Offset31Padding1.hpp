// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.0: types/Offset31Padding1.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// 1 bytes padding
struct Offset31Padding1 {

    static constexpr auto name = "Offset 31 Padding 1";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Offset31Padding1()
     : value{} {}

  protected:
    type value;
};
}
