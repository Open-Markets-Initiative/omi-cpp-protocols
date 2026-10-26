#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// The version number of the message schema that was used to encode a message
struct Version {

    static constexpr const char* name = "Version";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type static_value = 259;

    // default constructor
    constexpr Version()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Version(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of Version field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
