#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The bid reference number associated with the new quote.
struct BidReferenceNumber {

    static constexpr const char* name = "Bid Reference Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr BidReferenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidReferenceNumber(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of BidReferenceNumber field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
