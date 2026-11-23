// Nyse.ArcaOptions.DeepFeed.Pillar.v1.2.m: types/Reserved3.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {


// Reserved for future use
struct Reserved3 {

    static constexpr auto name = "Reserved 3";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved3()
     : value{} {}

  protected:
    type value;
};
}
