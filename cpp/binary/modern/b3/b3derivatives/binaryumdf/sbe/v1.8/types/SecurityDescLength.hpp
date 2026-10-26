#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {


// Length in bytes of the security description text
struct SecurityDescLength {

    static constexpr auto name = "Security Desc Length";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SecurityDescLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityDescLength(const std::uint8_t &value)
     : value{ value } {}

    // get value of SecurityDescLength field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
