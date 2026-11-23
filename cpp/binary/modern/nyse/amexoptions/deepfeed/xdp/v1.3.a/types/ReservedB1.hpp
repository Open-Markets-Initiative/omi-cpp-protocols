// Nyse.AmexOptions.DeepFeed.Xdp.v1.3.a: types/ReservedB1.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {


// Filler
struct ReservedB1 {

    static constexpr auto name = "Reserved B 1";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr ReservedB1()
     : value{} {}

  protected:
    type value;
};
}
