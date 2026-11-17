// Nasdaq.NsmEquities.TotalView.Itch.v4.0: types/Reserved.hpp
#pragma once

#include <array>
#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v4_0 {


// Reserved.
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
