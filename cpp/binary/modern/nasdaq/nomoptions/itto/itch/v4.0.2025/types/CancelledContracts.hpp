#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The number of contracts to be removed from the display size of the order as the result of a cancellation.
struct CancelledContracts {

    static constexpr const char* name = "Cancelled Contracts";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr CancelledContracts()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CancelledContracts(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of CancelledContracts field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
