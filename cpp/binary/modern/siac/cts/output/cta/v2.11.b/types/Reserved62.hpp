// Siac.Cts.Output.Cta.v2.11.b: types/Reserved62.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {


// Space-filled. Field is reserved for future use
struct Reserved62 {

    static constexpr auto name = "Reserved 62";
    static constexpr std::size_t size = 62;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved62()
     : value{} {}

  protected:
    type value;
};
}
