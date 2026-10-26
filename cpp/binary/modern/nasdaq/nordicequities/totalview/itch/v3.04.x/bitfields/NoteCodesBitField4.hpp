#pragma once

#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Note codes, logical Or is used to identify multiple note codes
struct NoteCodesBitField4 {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Note Codes Bit Field 4";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type BbBuyBack = 0x01;
        static const type CeCappedByEsma = 0x08;
        static const type PdPriceDiscrepancyHistoricalAverageShareClasses = 0x20;
        static const type SmStressedMarket = 0x40;
        static const type EwMarketwideExceptionalCircumstance = 0x80;
    };

    // default constructor
    constexpr NoteCodesBitField4()
     : value{ 0 } {}

    // 
    [[nodiscard]] constexpr bool BbBuyBack() const {
        return value & mask::BbBuyBack;
    }

    // 
    [[nodiscard]] constexpr bool CeCappedByEsma() const {
        return value & mask::CeCappedByEsma;
    }

    // 
    [[nodiscard]] constexpr bool PdPriceDiscrepancyHistoricalAverageShareClasses() const {
        return value & mask::PdPriceDiscrepancyHistoricalAverageShareClasses;
    }

    // 
    [[nodiscard]] constexpr bool SmStressedMarket() const {
        return value & mask::SmStressedMarket;
    }

    // 
    [[nodiscard]] constexpr bool EwMarketwideExceptionalCircumstance() const {
        return value & mask::EwMarketwideExceptionalCircumstance;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
