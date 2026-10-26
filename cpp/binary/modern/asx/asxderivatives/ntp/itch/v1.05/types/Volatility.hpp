#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Volatility for an option contract.
struct Volatility {

    static constexpr const char* name = "Volatility";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr Volatility()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Volatility(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of Volatility field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
