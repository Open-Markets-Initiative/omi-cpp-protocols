#pragma once

#include <array>
#include <cstddef>

namespace bse::bseindia::eobi::fbe::v1_4 {


// not used
struct Pad3 {

    static constexpr auto name = "Pad 3";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Pad3()
     : value{} {}

  protected:
    type value;
};
}
