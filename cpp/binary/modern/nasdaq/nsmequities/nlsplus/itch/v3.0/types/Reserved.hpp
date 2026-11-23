// Nasdaq.NsmEquities.NlsPlus.Itch.v3.0: types/Reserved.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Reserved for future use; space filled in the initial release
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
