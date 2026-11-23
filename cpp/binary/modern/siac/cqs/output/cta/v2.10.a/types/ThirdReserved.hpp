// Siac.Cqs.Output.Cta.v2.10.a: types/ThirdReserved.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v2_10_a {


// Space-filled. Field is reserved for future use
struct ThirdReserved {

    static constexpr auto name = "Third Reserved";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr ThirdReserved()
     : value{} {}

  protected:
    type value;
};
}
