#pragma once

#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Note codes, logical Or is used to identify multiple note codes
struct NoteCodesBitField5 {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Note Codes Bit Field 5";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type EmExceptionalCircumstancesRelatedToMarketMaker = 0x01;
        static const type UnUnderlyingNotQuoted = 0x02;
        static const type DaDigitalAsset = 0x04;
        static const type KnKnockOutBuyBackIntoNextTradingDay = 0x08;
    };

    // default constructor
    constexpr NoteCodesBitField5()
     : value{ 0 } {}

    // 
    [[nodiscard]] constexpr bool EmExceptionalCircumstancesRelatedToMarketMaker() const {
        return value & mask::EmExceptionalCircumstancesRelatedToMarketMaker;
    }

    // 
    [[nodiscard]] constexpr bool UnUnderlyingNotQuoted() const {
        return value & mask::UnUnderlyingNotQuoted;
    }

    // 
    [[nodiscard]] constexpr bool DaDigitalAsset() const {
        return value & mask::DaDigitalAsset;
    }

    // 
    [[nodiscard]] constexpr bool KnKnockOutBuyBackIntoNextTradingDay() const {
        return value & mask::KnKnockOutBuyBackIntoNextTradingDay;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
