#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

// Modify Flags
struct ModifyFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Modify Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type Display = 0x01;
        static const type MaintainPriority = 0x02;
    };

    // default constructor
    constexpr ModifyFlags()
     : value{ 0 } {}

    // Order is displayed in the Sip quote
    [[nodiscard]] constexpr bool Display() const {
        return value & mask::Display;
    }

    // Order keeps its priority rather than resetting it
    [[nodiscard]] constexpr bool MaintainPriority() const {
        return value & mask::MaintainPriority;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
