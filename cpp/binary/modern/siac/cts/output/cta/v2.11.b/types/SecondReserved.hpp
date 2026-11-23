// Siac.Cts.Output.Cta.v2.11.b: types/SecondReserved.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {


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
