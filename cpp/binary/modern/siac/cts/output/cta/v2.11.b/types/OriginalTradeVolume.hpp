#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Original total number of shares which traded in a single transaction for an individual security
struct OriginalTradeVolume {

    static constexpr const char* name = "Original Trade Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OriginalTradeVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalTradeVolume(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of OriginalTradeVolume field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
