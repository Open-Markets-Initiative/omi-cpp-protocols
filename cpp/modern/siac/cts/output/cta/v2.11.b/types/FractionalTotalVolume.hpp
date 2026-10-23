#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Contains Total Volume of shares traded in a security either on a Consolidated or an individual Participant basis. Has implied 6 decimal places
struct FractionalTotalVolume {

    static constexpr const char* name = "Fractional Total Volume";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr FractionalTotalVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FractionalTotalVolume(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of FractionalTotalVolume field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
