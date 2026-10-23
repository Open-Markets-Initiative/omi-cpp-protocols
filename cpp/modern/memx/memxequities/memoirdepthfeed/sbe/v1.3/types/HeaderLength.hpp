#pragma once

#include <cstddef>
#include <cstdint>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {


// Total bytes in this header
struct HeaderLength {

    static constexpr auto name = "Header Length";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr HeaderLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit HeaderLength(const std::uint8_t &value)
     : value{ value } {}

    // get value of HeaderLength field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
