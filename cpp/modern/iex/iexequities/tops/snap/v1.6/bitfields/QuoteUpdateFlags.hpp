#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::tops::snap::v1_6 {

// Quote Update Flags
struct QuoteUpdateFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Quote Update Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type MarketSession = 0x40;
        static const type SymbolAvailability = 0x80;
    };

    // default constructor
    constexpr QuoteUpdateFlags()
     : value{ 0 } {}

    // Market Session Flag
    [[nodiscard]] constexpr bool MarketSession() const {
        return value & mask::MarketSession;
    }

    // Symbol is halted, paused, or otherwise not available for trading on IEX
    [[nodiscard]] constexpr bool SymbolAvailability() const {
        return value & mask::SymbolAvailability;
    }

  protected:
    type value;
};
}
