#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The new reference number associated with the new order.
struct NewReferenceNumber {

    static constexpr const char* name = "New Reference Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr NewReferenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NewReferenceNumber(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of NewReferenceNumber field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
