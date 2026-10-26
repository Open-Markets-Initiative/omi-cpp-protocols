#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The order/quote reference number associated with the executed order.
struct ReferenceNumber {

    static constexpr const char* name = "Reference Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr ReferenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ReferenceNumber(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of ReferenceNumber field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
