#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Original total number of shares which traded in a single transaction. Has implied 6 decimal places
struct OriginalFractionalTradeVolume {

    static constexpr const char* name = "Original Fractional Trade Volume";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr OriginalFractionalTradeVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalFractionalTradeVolume(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of OriginalFractionalTradeVolume field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
