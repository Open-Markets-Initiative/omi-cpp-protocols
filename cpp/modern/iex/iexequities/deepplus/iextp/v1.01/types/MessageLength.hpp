#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deepplus::iextp::v1_01 {

// Length of the message
struct MessageLength {

    static constexpr const char* name = "Message Length";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr MessageLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MessageLength(const std::uint16_t value)
     : value{ value } {}

    // get value of MessageLength field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
