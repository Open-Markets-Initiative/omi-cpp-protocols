#pragma once

#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Note codes, logical Or is used to identify multiple note codes
struct NoteCodesBitField3 {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Note Codes Bit Field 3";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type SsExcludingCombSplitRedemptionShare = 0x01;
        static const type FnFirstNorthCompany = 0x02;
        static const type ObObservationStatus = 0x04;
        static const type XdExcludingDividend = 0x08;
        static const type FeForeignNonEueeaEntity = 0x10;
        static const type SoSoldOutBuyBack = 0x20;
        static const type SkSoftKnock = 0x40;
        static const type KbKnockOutBuyBack = 0x80;
    };

    // default constructor
    constexpr NoteCodesBitField3()
     : value{ 0 } {}

    // 
    [[nodiscard]] constexpr bool SsExcludingCombSplitRedemptionShare() const {
        return value & mask::SsExcludingCombSplitRedemptionShare;
    }

    // 
    [[nodiscard]] constexpr bool FnFirstNorthCompany() const {
        return value & mask::FnFirstNorthCompany;
    }

    // 
    [[nodiscard]] constexpr bool ObObservationStatus() const {
        return value & mask::ObObservationStatus;
    }

    // 
    [[nodiscard]] constexpr bool XdExcludingDividend() const {
        return value & mask::XdExcludingDividend;
    }

    // 
    [[nodiscard]] constexpr bool FeForeignNonEueeaEntity() const {
        return value & mask::FeForeignNonEueeaEntity;
    }

    // 
    [[nodiscard]] constexpr bool SoSoldOutBuyBack() const {
        return value & mask::SoSoldOutBuyBack;
    }

    // 
    [[nodiscard]] constexpr bool SkSoftKnock() const {
        return value & mask::SkSoftKnock;
    }

    // 
    [[nodiscard]] constexpr bool KbKnockOutBuyBack() const {
        return value & mask::KbKnockOutBuyBack;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
