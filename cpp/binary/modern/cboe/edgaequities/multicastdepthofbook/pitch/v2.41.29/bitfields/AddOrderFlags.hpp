#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

// Add Order Flags
struct AddOrderFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Add Order Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type Display = 0x01;
    };

    // default constructor
    constexpr AddOrderFlags()
     : value{ 0 } {}

    // Order is displayed in the Cboe SIP quote
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
