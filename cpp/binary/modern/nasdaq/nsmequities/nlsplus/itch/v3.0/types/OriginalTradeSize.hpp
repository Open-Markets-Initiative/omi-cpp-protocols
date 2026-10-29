#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The number of shares reported on the original trade transaction
struct OriginalTradeSize {

    static constexpr const char* name = "Original Trade Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr OriginalTradeSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalTradeSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of OriginalTradeSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
