#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Length of this message
struct MsgLength {

    static constexpr const char* name = "Msg Length";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr MsgLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MsgLength(const std::uint16_t value)
     : value{ value } {}

    // get value of MsgLength field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
