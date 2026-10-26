#pragma once

#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Note codes, logical Or is used to identify multiple note codes
struct NoteCodesBitField1 {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Note Codes Bit Field 1";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type NmNewMarketCompany = 0x01;
        static const type XrExcludingParticipatingInRights = 0x02;
        static const type SpExcludingParticipatingInSplit = 0x04;
        static const type PoCompanySubjectToPublicOffer = 0x08;
        static const type UdUnderDrawing = 0x10;
        static const type SrExcludingCombSplitAndIssueRights = 0x20;
        static const type UlUnListed = 0x40;
        static const type WiWhenIssued = 0x80;
    };

    // default constructor
    constexpr NoteCodesBitField1()
     : value{ 0 } {}

    // 
    [[nodiscard]] constexpr bool NmNewMarketCompany() const {
        return value & mask::NmNewMarketCompany;
    }

    // 
    [[nodiscard]] constexpr bool XrExcludingParticipatingInRights() const {
        return value & mask::XrExcludingParticipatingInRights;
    }

    // 
    [[nodiscard]] constexpr bool SpExcludingParticipatingInSplit() const {
        return value & mask::SpExcludingParticipatingInSplit;
    }

    // 
    [[nodiscard]] constexpr bool PoCompanySubjectToPublicOffer() const {
        return value & mask::PoCompanySubjectToPublicOffer;
    }

    // 
    [[nodiscard]] constexpr bool UdUnderDrawing() const {
        return value & mask::UdUnderDrawing;
    }

    // 
    [[nodiscard]] constexpr bool SrExcludingCombSplitAndIssueRights() const {
        return value & mask::SrExcludingCombSplitAndIssueRights;
    }

    // 
    [[nodiscard]] constexpr bool UlUnListed() const {
        return value & mask::UlUnListed;
    }

    // 
    [[nodiscard]] constexpr bool WiWhenIssued() const {
        return value & mask::WiWhenIssued;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
