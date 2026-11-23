// Bse.BseIndia.Eobi.Fbe.v1.4: types/Pad4.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// not used
struct Pad4 {

    static constexpr auto name = "Pad 4";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Pad4()
     : value{} {}

  protected:
    type value;
};
}
