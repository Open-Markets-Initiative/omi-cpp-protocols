#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::itch::v1_6 {

// Number of shares executed.
struct ExecutedQuantity {

    static constexpr const char* name = "Executed Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ExecutedQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExecutedQuantity(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of ExecutedQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
