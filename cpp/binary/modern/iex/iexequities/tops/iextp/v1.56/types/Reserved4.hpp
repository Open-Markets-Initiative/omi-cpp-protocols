// Iex.IexEquities.Tops.IexTp.v1.56: types/Reserved4.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace iex::iexequities::tops::iextp::v1_56 {


// Reserved bytes
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
