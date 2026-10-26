#pragma once

#include <array>
#include <cstddef>

namespace lseg::millennium::level2::mitch::v11_9 {


// Reserved field
struct Reserved10 {

    static constexpr auto name = "Reserved 10";
    static constexpr std::size_t size = 10;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved10()
     : value{} {}

  protected:
    type value;
};
}
