// Iex.IexEquities.DeepPlus.Snap.v1.06: types/Reserved.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deepplus::snap::v1_06 {


// Reserved byte
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
