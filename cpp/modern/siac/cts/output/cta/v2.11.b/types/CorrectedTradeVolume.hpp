#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Corrected total number of shares which traded in a single transaction for an individual security
struct CorrectedTradeVolume {

    static constexpr const char* name = "Corrected Trade Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr CorrectedTradeVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CorrectedTradeVolume(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of CorrectedTradeVolume field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
