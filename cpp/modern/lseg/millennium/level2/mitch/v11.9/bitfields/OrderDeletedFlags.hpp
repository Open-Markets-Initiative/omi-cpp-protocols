#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// Order Deleted Flags
struct OrderDeletedFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Order Deleted Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type Unused5 = 0x1F;
        static const type FirmQuote = 0x20;
        static const type Unused2 = 0xC0;
    };

    // default constructor
    constexpr OrderDeletedFlags()
     : value{ 0 } {}

    // Unused
    [[nodiscard]] constexpr bool Unused5() const {
        return value & mask::Unused5;
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
