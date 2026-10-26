#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Contains the Consolidated Total Volume of shares traded for a security at the time of the trade correction or cancel/error
struct ConsolidatedTotalVolume {

    static constexpr const char* name = "Consolidated Total Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ConsolidatedTotalVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ConsolidatedTotalVolume(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of ConsolidatedTotalVolume field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
