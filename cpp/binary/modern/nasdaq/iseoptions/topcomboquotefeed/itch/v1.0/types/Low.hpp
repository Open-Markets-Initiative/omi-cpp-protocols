#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Low price for the day.
struct Low {

    static constexpr const char* name = "Low";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr Low()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Low(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of Low field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
