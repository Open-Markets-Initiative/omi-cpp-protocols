#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// Modify Flags bit field used in Modify Order messages. Bit 0 indicates whether the order is aggregated in the Cboe SIP quote; Bit 1 indicates whether priority is maintained or reset.
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

    // 0 = Order is not aggregated in the Cboe SIP quote, 1 = Order is aggregated in the Cboe SIP quote.
    [[nodiscard]] constexpr bool Display() const {
        return value & mask::Display;
    }

    // 0 = Reset Priority, 1 = Maintain Priority.
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
