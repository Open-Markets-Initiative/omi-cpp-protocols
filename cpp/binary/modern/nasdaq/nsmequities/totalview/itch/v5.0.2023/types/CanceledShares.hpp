#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// The number of shares being removed from the display size of the order as the result of a cancellation
struct CanceledShares {

    static constexpr const char* name = "Canceled Shares";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr CanceledShares()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CanceledShares(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of CanceledShares field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
