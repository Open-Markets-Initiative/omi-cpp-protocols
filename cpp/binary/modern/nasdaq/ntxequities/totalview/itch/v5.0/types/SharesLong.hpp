#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

// The number of shares matched in the Nasdaq Texas Cross.
struct SharesLong {

    static constexpr const char* name = "Shares Long";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr SharesLong()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SharesLong(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of SharesLong field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
