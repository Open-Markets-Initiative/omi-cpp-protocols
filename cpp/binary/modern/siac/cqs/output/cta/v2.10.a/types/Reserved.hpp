// Siac.Cqs.Output.Cta.v2.10.a: types/Reserved.hpp
#pragma once

#include <array>
#include <cstddef>

namespace siac::cqs::output::cta::v2_10_a {


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
