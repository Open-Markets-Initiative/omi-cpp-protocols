// Siac.Cqs.Output.Cta.v2.10.a: types/Reserved128.hpp
#pragma once

#include <array>
#include <cstddef>

namespace siac::cqs::output::cta::v2_10_a {


// Space-filled. Field is reserved for future use
struct Reserved128 {

    static constexpr auto name = "Reserved 128";
    static constexpr std::size_t size = 128;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved128()
     : value{} {}

  protected:
    type value;
};
}
