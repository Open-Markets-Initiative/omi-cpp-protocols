#pragma once

#include <array>
#include <cstddef>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {


// Reserved for future use.
struct ThirdReserved2 {

    static constexpr auto name = "Third Reserved 2";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr ThirdReserved2()
     : value{} {}

  protected:
    type value;
};
}
