#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// Add Attributed Order Flags
struct AddAttributedOrderFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Add Attributed Order Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type Unused4 = 0x0F;
        static const type NamedMarketOrder = 0x10;
        static const type FirmQuote = 0x20;
        static const type Unused2 = 0xC0;
    };

    // default constructor
    constexpr AddAttributedOrderFlags()
     : value{ 0 } {}

    // Unused
    [[nodiscard]] constexpr bool Unused4() const {
        return value & mask::Unused4;
    }

    // Named Market Order
    [[nodiscard]] constexpr bool NamedMarketOrder() const {
        return value & mask::NamedMarketOrder;
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
