#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The ask reference number associated with the new quote
struct AskReferenceNumber {

    static constexpr const char* name = "Ask Reference Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr AskReferenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AskReferenceNumber(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of AskReferenceNumber field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
