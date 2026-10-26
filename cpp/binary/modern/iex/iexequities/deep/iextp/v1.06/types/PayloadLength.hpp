#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deep::iextp::v1_06 {

// Byte length of the payload
struct PayloadLength {

    static constexpr const char* name = "Payload Length";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr PayloadLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PayloadLength(const std::uint16_t value)
     : value{ value } {}

    // get value of PayloadLength field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
