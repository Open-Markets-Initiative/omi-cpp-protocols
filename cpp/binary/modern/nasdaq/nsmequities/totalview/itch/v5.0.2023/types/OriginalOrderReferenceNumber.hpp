#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// The original reference number of the order being replaced
struct OriginalOrderReferenceNumber {

    static constexpr const char* name = "Original Order Reference Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr OriginalOrderReferenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalOrderReferenceNumber(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of OriginalOrderReferenceNumber field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
