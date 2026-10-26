#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// RoundLot
struct RoundLot {

    static constexpr const char* name = "Round Lot";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr RoundLot()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RoundLot(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of RoundLot field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
