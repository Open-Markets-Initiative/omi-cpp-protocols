// Bse.BseIndia.Eobi.Fbe.v1.4: types/Pad6.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// not used
struct Pad6 {

    static constexpr auto name = "Pad 6";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Pad6()
     : value{} {}

  protected:
    type value;
};
}
