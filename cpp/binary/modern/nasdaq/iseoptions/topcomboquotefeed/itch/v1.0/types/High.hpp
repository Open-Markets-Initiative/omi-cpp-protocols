#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// High price for the day.
struct High {

    static constexpr const char* name = "High";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr High()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit High(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of High field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
