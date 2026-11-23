// Nyse.ArcaOptions.DeepFeed.Pillar.v1.2.m: types/SecondReserved2.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {


// Reserved for future use.
struct SecondReserved2 {

    static constexpr auto name = "Second Reserved 2";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr SecondReserved2()
     : value{} {}

  protected:
    type value;
};
}
