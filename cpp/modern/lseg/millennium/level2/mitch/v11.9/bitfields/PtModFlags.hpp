#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// Indicates a trade cancellation or amendment
struct PtModFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Pt Mod Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type Canc = 0x01;
        static const type Amnd = 0x02;
        static const type Unused6 = 0xFC;
    };

    // default constructor
    constexpr PtModFlags()
     : value{ 0 } {}

    // Cancel
    [[nodiscard]] constexpr bool Canc() const {
        return value & mask::Canc;
    }

    // Amended
    [[nodiscard]] constexpr bool Amnd() const {
        return value & mask::Amnd;
    }

    // Unused
    [[nodiscard]] constexpr bool Unused6() const {
        return value & mask::Unused6;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
