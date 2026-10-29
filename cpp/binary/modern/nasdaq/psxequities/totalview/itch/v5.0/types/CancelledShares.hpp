#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::psxequities::totalview::itch::v5_0 {

// The number of shares being removed from the display size of the order as the result of a cancellation.
struct CancelledShares {

    static constexpr const char* name = "Cancelled Shares";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr CancelledShares()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CancelledShares(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of CancelledShares field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
