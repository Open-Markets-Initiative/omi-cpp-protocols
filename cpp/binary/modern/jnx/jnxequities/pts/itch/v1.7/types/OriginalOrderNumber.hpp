#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::itch::v1_7 {

// Reference number of the original order.
struct OriginalOrderNumber {

    static constexpr const char* name = "Original Order Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr OriginalOrderNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalOrderNumber(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of OriginalOrderNumber field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
