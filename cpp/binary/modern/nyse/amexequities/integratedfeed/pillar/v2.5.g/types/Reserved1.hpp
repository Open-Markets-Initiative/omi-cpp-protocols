// Nyse.AmexEquities.IntegratedFeed.Pillar.v2.5.g: types/Reserved1.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace nyse::amexequities::integratedfeed::pillar::v2_5_g {


// Defaulted to 0. Future use only.
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
