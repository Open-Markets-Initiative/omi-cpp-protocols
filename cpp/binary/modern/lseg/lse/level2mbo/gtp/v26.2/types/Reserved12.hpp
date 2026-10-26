#pragma once

#include <array>
#include <cstddef>

namespace lseg::lse::level2mbo::gtp::v26_2 {


// Reserved for future use.
struct Reserved12 {

    static constexpr auto name = "Reserved 12";
    static constexpr std::size_t size = 12;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved12()
     : value{} {}

  protected:
    type value;
};
}
