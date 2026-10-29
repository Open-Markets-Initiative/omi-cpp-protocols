#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// The Nav offset originally applied to the Proxy Price
struct OriginalNavOffsetAmount {

    static constexpr const char* name = "Original Nav Offset Amount";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr OriginalNavOffsetAmount()
     : value{ 0 } {}

    // constructor for OriginalNavOffsetAmount field
    constexpr explicit OriginalNavOffsetAmount(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of OriginalNavOffsetAmount field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of OriginalNavOffsetAmount field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
