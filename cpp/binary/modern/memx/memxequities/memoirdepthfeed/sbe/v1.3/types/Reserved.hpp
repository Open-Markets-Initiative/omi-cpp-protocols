// Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3: types/Reserved.hpp
#pragma once

#include <array>
#include <cstddef>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {


// Reserved
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
