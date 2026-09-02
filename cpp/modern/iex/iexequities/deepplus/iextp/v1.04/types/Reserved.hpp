#pragma once

#include <array>
#include <cstddef>

namespace iex::iexequities::deepplus::iextp::v1_04 {


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
