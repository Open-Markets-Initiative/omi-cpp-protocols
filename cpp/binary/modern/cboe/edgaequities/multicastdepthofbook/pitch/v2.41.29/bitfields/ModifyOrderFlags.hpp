#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

// Modify Order Flags
struct ModifyOrderFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Modify Order Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type Display = 0x01;
        static const type Priority = 0x02;
    };

    // default constructor
    constexpr ModifyOrderFlags()
     : value{ 0 } {}

    // Order is displayed in the Cboe SIP quote
    [[nodiscard]] constexpr bool Display() const {
        return value & mask::Display;
    }

    // Maintain Priority
    [[nodiscard]] constexpr bool Priority() const {
        return value & mask::Priority;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
