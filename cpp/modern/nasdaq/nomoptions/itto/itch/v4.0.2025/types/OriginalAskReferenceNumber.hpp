#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The original ask reference number that is replaced
struct OriginalAskReferenceNumber {

    static constexpr const char* name = "Original Ask Reference Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr OriginalAskReferenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalAskReferenceNumber(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of OriginalAskReferenceNumber field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
