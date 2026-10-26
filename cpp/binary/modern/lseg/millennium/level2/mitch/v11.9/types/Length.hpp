#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// Length of the message block including the header and all payload messages
struct Length {

    static constexpr const char* name = "Length";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr Length()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Length(const std::uint16_t value)
     : value{ value } {}

    // get value of Length field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
