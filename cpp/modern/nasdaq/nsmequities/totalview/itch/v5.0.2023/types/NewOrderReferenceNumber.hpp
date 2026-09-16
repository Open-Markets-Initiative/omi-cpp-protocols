#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// The new reference number for this order at time of replacement
struct NewOrderReferenceNumber {

    static constexpr const char* name = "New Order Reference Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr NewOrderReferenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NewOrderReferenceNumber(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of NewOrderReferenceNumber field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
