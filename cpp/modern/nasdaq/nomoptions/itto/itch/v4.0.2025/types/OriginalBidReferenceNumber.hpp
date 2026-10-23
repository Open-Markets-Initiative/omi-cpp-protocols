#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The original bid reference number that is replaced
struct OriginalBidReferenceNumber {

    static constexpr const char* name = "Original Bid Reference Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr OriginalBidReferenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalBidReferenceNumber(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of OriginalBidReferenceNumber field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
