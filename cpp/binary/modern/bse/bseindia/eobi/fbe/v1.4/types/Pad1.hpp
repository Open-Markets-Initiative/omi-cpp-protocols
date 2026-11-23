// Bse.BseIndia.Eobi.Fbe.v1.4: types/Pad1.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// not used
struct Pad1 {

    static constexpr auto name = "Pad 1";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Pad1()
     : value{} {}

  protected:
    type value;
};
}
