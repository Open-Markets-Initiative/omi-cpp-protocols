// Nyse.TexasEquities.IntegratedFeed.Pillar.v2.5.g: types/Reserved4.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {


// Future use. Any field content should be ignored.
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
