#pragma once

#include <array>
#include <cstddef>

namespace siac::opra::output::obi::v6_2 {


// One reserved byte
struct Reserved1 {

    static constexpr auto name = "Reserved 1";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved1()
     : value{} {}

  protected:
    type value;
};
}
