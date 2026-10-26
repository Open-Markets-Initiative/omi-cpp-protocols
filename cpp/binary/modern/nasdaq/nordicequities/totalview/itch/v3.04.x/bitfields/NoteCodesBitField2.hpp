#pragma once

#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Note codes, logical Or is used to identify multiple note codes
struct NoteCodesBitField2 {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Note Codes Bit Field 2";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type BrCompanyBankruptcy = 0x01;
        static const type SuSuspension = 0x02;
        static const type RlRemovalFromListingInProcess = 0x04;
        static const type SlOtherSurveillanceListReason = 0x08;
        static const type ToASignificantReverseTakeoverPending = 0x10;
        static const type CsCentShares = 0x20;
        static const type RsReversedSplit = 0x40;
        static const type BsExcludingCombBonusSplit = 0x80;
    };

    // default constructor
    constexpr NoteCodesBitField2()
     : value{ 0 } {}

    // 
    [[nodiscard]] constexpr bool BrCompanyBankruptcy() const {
        return value & mask::BrCompanyBankruptcy;
    }

    // 
    [[nodiscard]] constexpr bool SuSuspension() const {
        return value & mask::SuSuspension;
    }

    // 
    [[nodiscard]] constexpr bool RlRemovalFromListingInProcess() const {
        return value & mask::RlRemovalFromListingInProcess;
    }

    // 
    [[nodiscard]] constexpr bool SlOtherSurveillanceListReason() const {
        return value & mask::SlOtherSurveillanceListReason;
    }

    // 
    [[nodiscard]] constexpr bool ToASignificantReverseTakeoverPending() const {
        return value & mask::ToASignificantReverseTakeoverPending;
    }

    // 
    [[nodiscard]] constexpr bool CsCentShares() const {
        return value & mask::CsCentShares;
    }

    // 
    [[nodiscard]] constexpr bool RsReversedSplit() const {
        return value & mask::RsReversedSplit;
    }

    // 
    [[nodiscard]] constexpr bool BsExcludingCombBonusSplit() const {
        return value & mask::BsExcludingCombBonusSplit;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
