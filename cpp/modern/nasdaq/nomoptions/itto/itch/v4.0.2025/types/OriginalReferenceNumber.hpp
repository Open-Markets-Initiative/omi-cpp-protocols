#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The original reference number associated with the order being replaced.
struct OriginalReferenceNumber {

    static constexpr const char* name = "Original Reference Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr OriginalReferenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalReferenceNumber(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of OriginalReferenceNumber field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
