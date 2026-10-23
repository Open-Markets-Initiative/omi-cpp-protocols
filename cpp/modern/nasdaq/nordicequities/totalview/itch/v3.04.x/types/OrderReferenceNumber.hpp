#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Unique reference number assigned to the new order
struct OrderReferenceNumber {

    static constexpr const char* name = "Order Reference Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr OrderReferenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderReferenceNumber(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of OrderReferenceNumber field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
