#pragma once

#include <array>
#include <cstddef>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {


// Reserved for Future use
struct Reserved2 {

    static constexpr auto name = "Reserved 2";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved2()
     : value{} {}

  protected:
    type value;
};
}
