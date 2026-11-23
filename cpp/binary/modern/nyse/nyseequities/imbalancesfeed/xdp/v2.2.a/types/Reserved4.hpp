// Nyse.NyseEquities.ImbalancesFeed.Xdp.v2.2.a: types/Reserved4.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {


// Future use. Any field content should be ignored.
struct Reserved4 {

    static constexpr auto name = "Reserved 4";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved4()
     : value{} {}

  protected:
    type value;
};
}
