#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jnx::jnxequities::pts::itch::v1_7 {

// Reference number of the replaced order.
struct NewOrderNumber {

    static constexpr const char* name = "New Order Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr NewOrderNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NewOrderNumber(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of NewOrderNumber field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
