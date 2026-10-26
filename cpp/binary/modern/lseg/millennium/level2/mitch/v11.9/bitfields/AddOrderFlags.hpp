#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// Add Order Flags
struct AddOrderFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Add Order Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type Unused4 = 0x0F;
        static const type MarketOrder = 0x10;
        static const type Unused1 = 0x20;
        static const type PrivateRfq = 0x40;
        static const type SecondUnused1 = 0x80;
    };

    // default constructor
    constexpr AddOrderFlags()
     : value{ 0 } {}

    // Unused
    [[nodiscard]] constexpr bool Unused4() const {
        return value & mask::Unused4;
    }

    // Market Order
    [[nodiscard]] constexpr bool MarketOrder() const {
        return value & mask::MarketOrder;
    }

    // Unused
    [[nodiscard]] constexpr bool Unused1() const {
        return value & mask::Unused1;
    }

    // Private RFQ
    [[nodiscard]] constexpr bool PrivateRfq() const {
        return value & mask::PrivateRfq;
    }

    // Unused
    [[nodiscard]] constexpr bool SecondUnused1() const {
        return value & mask::SecondUnused1;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
