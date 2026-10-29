#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Order entry firm identifier
struct FirmId {

    static constexpr const char* name = "Firm Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr FirmId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FirmId(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of FirmId field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
