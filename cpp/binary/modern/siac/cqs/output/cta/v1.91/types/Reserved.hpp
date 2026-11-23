// Siac.Cqs.Output.Cta.v1.91: types/Reserved.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace siac::cqs::output::cta::v1_91 {


// Field is reserved for future use.
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
