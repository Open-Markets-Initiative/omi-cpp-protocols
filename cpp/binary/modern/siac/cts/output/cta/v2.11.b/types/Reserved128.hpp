// Siac.Cts.Output.Cta.v2.11.b: types/Reserved128.hpp
#pragma once

#include <array>
#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


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
