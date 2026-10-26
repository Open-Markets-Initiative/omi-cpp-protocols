#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// Add Flags bit field used in Add Order messages. Bit 3 indicates AON (All or None) status (Options only).
struct AddFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Add Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type Aon = 0x08;
    };

    // default constructor
    constexpr AddFlags()
     : value{ 0 } {}

    // Options only. 0 = Order is a firm quote, 1 = Order is AON (All or None).
    [[nodiscard]] constexpr bool Aon() const {
        return value & mask::Aon;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
