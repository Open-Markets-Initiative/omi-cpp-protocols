#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The corrected Nav offset applied to the Proxy Price
struct CorrectedNavOffsetAmount {

    static constexpr const char* name = "Corrected Nav Offset Amount";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr CorrectedNavOffsetAmount()
     : value{ 0 } {}

    // constructor for CorrectedNavOffsetAmount field
    constexpr explicit CorrectedNavOffsetAmount(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of CorrectedNavOffsetAmount field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of CorrectedNavOffsetAmount field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
