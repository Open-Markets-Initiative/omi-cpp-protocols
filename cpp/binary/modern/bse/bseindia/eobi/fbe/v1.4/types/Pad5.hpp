#pragma once

#include <array>
#include <cstddef>

namespace bse::bseindia::eobi::fbe::v1_4 {


// not used
struct Pad5 {

    static constexpr auto name = "Pad 5";
    static constexpr std::size_t size = 5;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Pad5()
     : value{} {}

  protected:
    type value;
};
}
