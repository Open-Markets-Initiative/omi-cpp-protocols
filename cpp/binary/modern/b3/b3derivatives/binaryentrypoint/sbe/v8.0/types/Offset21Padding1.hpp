#pragma once

#include <array>
#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// 1 bytes padding
struct Offset21Padding1 {

    static constexpr auto name = "Offset 21 Padding 1";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Offset21Padding1()
     : value{} {}

  protected:
    type value;
};
}
