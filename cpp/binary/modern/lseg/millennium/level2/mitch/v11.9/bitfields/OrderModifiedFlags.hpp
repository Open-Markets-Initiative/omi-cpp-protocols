#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// Order Modified Flags
struct OrderModifiedFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Order Modified Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type PriorityFlag = 0x01;
        static const type Unused4 = 0x1E;
        static const type FirmQuote = 0x20;
        static const type Unused2 = 0xC0;
    };

    // default constructor
    constexpr OrderModifiedFlags()
     : value{ 0 } {}

    // Priority Flag
    [[nodiscard]] constexpr bool PriorityFlag() const {
        return value & mask::PriorityFlag;
    }

    // Unused
    [[nodiscard]] constexpr bool Unused4() const {
        return value & mask::Unused4;
    }

    // Firm Quote
    [[nodiscard]] constexpr bool FirmQuote() const {
        return value & mask::FirmQuote;
    }

    // Unused
    [[nodiscard]] constexpr bool Unused2() const {
        return value & mask::Unused2;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
