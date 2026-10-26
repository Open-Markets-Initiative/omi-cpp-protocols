#pragma once

#include <array>
#include <cstddef>

namespace iex::iexequities::tops::iextp::v1_56 {


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
