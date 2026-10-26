#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::millennium::level2::mitch::v11_9 {

// Order Book Clear Flags
struct OrderBookClearFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Order Book Clear Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type Unused5 = 0x1F;
        static const type FirmQuote = 0x20;
        static const type PrivateRfq = 0x40;
        static const type Unused1 = 0x80;
    };

    // default constructor
    constexpr OrderBookClearFlags()
     : value{ 0 } {}

    // Unused
    [[nodiscard]] constexpr bool Unused5() const {
        return value & mask::Unused5;
    }

    // Firm Quote
    [[nodiscard]] constexpr bool FirmQuote() const {
        return value & mask::FirmQuote;
    }

    // Private RFQ
    [[nodiscard]] constexpr bool PrivateRfq() const {
        return value & mask::PrivateRfq;
    }

    // Unused
    [[nodiscard]] constexpr bool Unused1() const {
        return value & mask::Unused1;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
