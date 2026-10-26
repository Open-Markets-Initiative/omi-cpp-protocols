#pragma once

#include <array>
#include <cstddef>

namespace lseg::lse::level2mbo::gtp::v26_2 {


// Reserved for future use.
struct Reserved11 {

    static constexpr auto name = "Reserved 11";
    static constexpr std::size_t size = 11;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved11()
     : value{} {}

  protected:
    type value;
};
}
