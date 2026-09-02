#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deep::iextp::v1_08 {

// Sale Condition Flags
struct SaleConditionFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Sale Condition Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type SinglepriceCrossTrade = 0x08;
        static const type TradeThroughExempt = 0x10;
        static const type OddLot = 0x20;
        static const type ExtendedHours = 0x40;
        static const type IntermarketSweep = 0x80;
    };

    // default constructor
    constexpr SaleConditionFlags()
     : value{ 0 } {}

    // Trade resulting from a single-price cross
    [[nodiscard]] constexpr bool SinglepriceCrossTrade() const {
        return value & mask::SinglepriceCrossTrade;
    }

    // Trade is not subject to Rule 611
    [[nodiscard]] constexpr bool TradeThroughExempt() const {
        return value & mask::TradeThroughExempt;
    }

    // Odd Lot
    [[nodiscard]] constexpr bool OddLot() const {
        return value & mask::OddLot;
    }

    // Extended Hours Trade
    [[nodiscard]] constexpr bool ExtendedHours() const {
        return value & mask::ExtendedHours;
    }

    // Intermarket Sweep Order
    [[nodiscard]] constexpr bool IntermarketSweep() const {
        return value & mask::IntermarketSweep;
    }

  protected:
    type value;
};
}
