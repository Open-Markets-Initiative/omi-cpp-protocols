#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Date of expiration
struct ExpirationDate {

    static constexpr const char* name = "Expiration Date";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ExpirationDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExpirationDate(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of ExpirationDate field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
