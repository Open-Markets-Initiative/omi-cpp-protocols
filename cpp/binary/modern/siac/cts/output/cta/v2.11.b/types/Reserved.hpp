// Siac.Cts.Output.Cta.v2.11.b: types/Reserved.hpp
#pragma once

#include <array>
#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Space-filled. Field is reserved for future use
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
