#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The number of shares reported on the corrected trade transaction
struct CorrectedTradeSize {

    static constexpr const char* name = "Corrected Trade Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr CorrectedTradeSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CorrectedTradeSize(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of CorrectedTradeSize field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
