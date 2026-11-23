// Jpx.OseDerivatives.GeniumInet.Itch.v5.0.6: types/Reserved24.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {


// Reserved
struct Reserved24 {

    static constexpr auto name = "Reserved 24";
    static constexpr std::size_t size = 24;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved24()
     : value{} {}

  protected:
    type value;
};
}
