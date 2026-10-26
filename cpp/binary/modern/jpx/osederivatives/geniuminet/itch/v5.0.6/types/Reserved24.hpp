#pragma once

#include <array>
#include <cstddef>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {


// Reserved
struct Reserved24 {

    static constexpr auto name = "Reserved 24";
    static constexpr std::size_t size = 24;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved24()
     : value{} {}

  protected:
    type value;
};
}
