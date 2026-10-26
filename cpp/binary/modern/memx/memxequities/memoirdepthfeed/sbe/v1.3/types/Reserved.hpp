#pragma once

#include <cstddef>
#include <cstdint>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {


// Reserved
struct Reserved {

    static constexpr auto name = "Reserved";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr Reserved()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Reserved(const std::uint8_t &value)
     : value{ value } {}

    // get value of Reserved field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
