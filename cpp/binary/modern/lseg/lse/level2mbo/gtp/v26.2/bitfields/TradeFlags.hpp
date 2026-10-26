#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Trade Flags
struct TradeFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Trade Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type TradeCancellation = 0x01;
        static const type TradeCorrection = 0x02;
    };

    // default constructor
    constexpr TradeFlags()
     : value{ 0 } {}

    // Trade Cancellation
    [[nodiscard]] constexpr bool TradeCancellation() const {
        return value & mask::TradeCancellation;
    }

    // Trade Correction
    [[nodiscard]] constexpr bool TradeCorrection() const {
        return value & mask::TradeCorrection;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
