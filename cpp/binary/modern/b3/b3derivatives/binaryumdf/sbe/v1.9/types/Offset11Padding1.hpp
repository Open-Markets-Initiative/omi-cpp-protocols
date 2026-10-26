#pragma once

#include <array>
#include <cstddef>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {


// 1 bytes padding
struct Offset11Padding1 {

    static constexpr auto name = "Offset 11 Padding 1";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Offset11Padding1()
     : value{} {}

  protected:
    type value;
};
}
