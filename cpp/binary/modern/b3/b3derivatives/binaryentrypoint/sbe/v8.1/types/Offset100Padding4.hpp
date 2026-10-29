#pragma once

#include <array>
#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// 4 bytes padding
struct Offset100Padding4 {

    static constexpr auto name = "Offset 100 Padding 4";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Offset100Padding4()
     : value{} {}

  protected:
    type value;
};
}
