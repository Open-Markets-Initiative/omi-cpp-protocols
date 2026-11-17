// Nasdaq.NsmEquities.TotalView.Itch.v5.0.2017: types/Reserved.hpp
#pragma once

#include <array>
#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {


// Reserved
struct Reserved {

    static constexpr auto name = "Reserved";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved()
     : value{} {}

  protected:
    type value;
};
}
