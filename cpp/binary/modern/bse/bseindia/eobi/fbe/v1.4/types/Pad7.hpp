#pragma once

#include <array>
#include <cstddef>

namespace bse::bseindia::eobi::fbe::v1_4 {


// not used
struct Pad7 {

    static constexpr auto name = "Pad 7";
    static constexpr std::size_t size = 7;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Pad7()
     : value{} {}

  protected:
    type value;
};
}
