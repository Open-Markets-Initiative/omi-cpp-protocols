#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// OriginalQuantity
struct OriginalQuantity {

    static constexpr const char* name = "Original Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OriginalQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalQuantity(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of OriginalQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
