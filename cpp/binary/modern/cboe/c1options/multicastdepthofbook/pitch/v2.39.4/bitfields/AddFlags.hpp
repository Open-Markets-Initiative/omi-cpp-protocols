#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// Add Flags bitfield struct
struct AddFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Add Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type Display = 0x01;
    };

    // default constructor
    constexpr AddFlags()
     : value{ 0 } {}

    // Display bits
    [[nodiscard]] constexpr bool Display() const {
        return value & mask::Display;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
