#pragma once

#include <array>
#include <cstddef>

namespace siac::opra::output::obi::v6_2 {


// Four reserved bytes
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
