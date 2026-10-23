#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Contains the total number of shares which traded in a single transaction for an individual security. Has implied 6 decimal places
struct FractionalTradeVolume {

    static constexpr const char* name = "Fractional Trade Volume";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr FractionalTradeVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FractionalTradeVolume(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of FractionalTradeVolume field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
