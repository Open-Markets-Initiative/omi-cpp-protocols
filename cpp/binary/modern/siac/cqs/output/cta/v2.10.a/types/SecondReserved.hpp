// Siac.Cqs.Output.Cta.v2.10.a: types/SecondReserved.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v2_10_a {


// Space-filled. Field is reserved for future use
struct SecondReserved {

    static constexpr auto name = "Second Reserved";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr SecondReserved()
     : value{} {}

  protected:
    type value;
};
}
