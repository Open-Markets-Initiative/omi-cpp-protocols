#pragma once

#include <array>
#include <cstddef>

namespace lseg::millennium::level2::mitch::v11_9 {


// Reserved field
struct Reserved4 {

    static constexpr auto name = "Reserved 4";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved4()
     : value{} {}

  protected:
    type value;
};
}
