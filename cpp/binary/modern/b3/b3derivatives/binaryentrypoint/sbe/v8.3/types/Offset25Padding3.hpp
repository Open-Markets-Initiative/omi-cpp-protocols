// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.3: types/Offset25Padding3.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// 3 bytes padding
struct Offset25Padding3 {

    static constexpr auto name = "Offset 25 Padding 3";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Offset25Padding3()
     : value{} {}

  protected:
    type value;
};
}
