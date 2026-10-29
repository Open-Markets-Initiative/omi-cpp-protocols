#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_10 {

// Contains the total number of shares traded in a single transaction for an individual security
struct TradeTotalVolume {

    static constexpr const char* name = "Trade Total Volume";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr TradeTotalVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TradeTotalVolume(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of TradeTotalVolume field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
