#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

// Length of entire block of messages. Includes this header and Message Count messages to follow
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
