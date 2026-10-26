#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// InstAttribValue bit set
struct InstAttribValue {

    // underlying type
    using type = std::uint32_t;

    static constexpr const char* name = "Inst Attrib Value";
    static constexpr std::size_t size = 4;

    struct mask {
        static const type ElectronicMatchEligible = 0x00000001;
        static const type OrderCrossEligible = 0x00000002;
        static const type BlockTradeEligible = 0x00000004;
        static const type EfpEligible = 0x00000008;
        static const type EbfEligible = 0x00000010;
        static const type EfsEligible = 0x00000020;
        static const type EfrEligible = 0x00000040;
        static const type OtcEligible = 0x00000080;
        static const type IlinkIndicativeMassQuotingEligible = 0x00000100;
        static const type NegativeStrikeEligible = 0x00000200;
        static const type NegativePriceOutrightEligible = 0x00000400;
        static const type IsFractional = 0x00000800;
        static const type VolatilityQuotedOption = 0x00001000;
        static const type RfqCrossEligible = 0x00002000;
        static const type ZeroPriceOutrightEligible = 0x00004000;
        static const type DecayingProductEligibility = 0x00008000;
        static const type VariableProductEligibility = 0x00010000;
        static const type DailyProductEligibility = 0x00020000;
        static const type GtOrdersEligibility = 0x00040000;
        static const type ImpliedMatchingEligibility = 0x00080000;
        static const type TriangulationEligible = 0x00100000;
        static const type VariableCabEligible = 0x00200000;
        static const type InvertedBook = 0x00400000;
        static const type IsAonInstrument = 0x00800000;
        static const type SefRegulated = 0x01000000;
        static const type MtfRegulated = 0x02000000;
        static const type EfixInstrument = 0x04000000;
        static const type HedgeInstrument = 0x08000000;
        static const type Reserved4 = 0xF0000000;
    };

    // default constructor
    constexpr InstAttribValue()
     : value{ 0 } {}

    // ElectronicMatchEligible
    [[nodiscard]] constexpr bool ElectronicMatchEligible() const {
        return value & mask::ElectronicMatchEligible;
    }

    // OrderCrossEligible
    [[nodiscard]] constexpr bool OrderCrossEligible() const {
        return value & mask::OrderCrossEligible;
    }

    // BlockTradeEligible
    [[nodiscard]] constexpr bool BlockTradeEligible() const {
        return value & mask::BlockTradeEligible;
    }

    // EFPEligible
    [[nodiscard]] constexpr bool EfpEligible() const {
        return value & mask::EfpEligible;
    }

    // EBFEligible
    [[nodiscard]] constexpr bool EbfEligible() const {
        return value & mask::EbfEligible;
    }

    // EFSEligible
    [[nodiscard]] constexpr bool EfsEligible() const {
        return value & mask::EfsEligible;
    }

    // EFREligible
    [[nodiscard]] constexpr bool EfrEligible() const {
        return value & mask::EfrEligible;
    }

    // OTCEligible
    [[nodiscard]] constexpr bool OtcEligible() const {
        return value & mask::OtcEligible;
    }

    // iLinkIndicativeMassQuotingEligible
    [[nodiscard]] constexpr bool IlinkIndicativeMassQuotingEligible() const {
        return value & mask::IlinkIndicativeMassQuotingEligible;
    }

    // NegativeStrikeEligible
    [[nodiscard]] constexpr bool NegativeStrikeEligible() const {
        return value & mask::NegativeStrikeEligible;
    }

    // NegativePriceOutrightEligible
    [[nodiscard]] constexpr bool NegativePriceOutrightEligible() const {
        return value & mask::NegativePriceOutrightEligible;
    }

    // IsFractional
    [[nodiscard]] constexpr bool IsFractional() const {
        return value & mask::IsFractional;
    }

    // VolatilityQuotedOption
    [[nodiscard]] constexpr bool VolatilityQuotedOption() const {
        return value & mask::VolatilityQuotedOption;
    }

    // RFQCrossEligible
    [[nodiscard]] constexpr bool RfqCrossEligible() const {
        return value & mask::RfqCrossEligible;
    }

    // ZeroPriceOutrightEligible
    [[nodiscard]] constexpr bool ZeroPriceOutrightEligible() const {
        return value & mask::ZeroPriceOutrightEligible;
    }

    // DecayingProductEligibility
    [[nodiscard]] constexpr bool DecayingProductEligibility() const {
        return value & mask::DecayingProductEligibility;
    }

    // VariableProductEligibility
    [[nodiscard]] constexpr bool VariableProductEligibility() const {
        return value & mask::VariableProductEligibility;
    }

    // DailyProductEligibility
    [[nodiscard]] constexpr bool DailyProductEligibility() const {
        return value & mask::DailyProductEligibility;
    }

    // GTOrdersEligibility
    [[nodiscard]] constexpr bool GtOrdersEligibility() const {
        return value & mask::GtOrdersEligibility;
    }

    // ImpliedMatchingEligibility
    [[nodiscard]] constexpr bool ImpliedMatchingEligibility() const {
        return value & mask::ImpliedMatchingEligibility;
    }

    // TriangulationEligible
    [[nodiscard]] constexpr bool TriangulationEligible() const {
        return value & mask::TriangulationEligible;
    }

    // VariableCabEligible
    [[nodiscard]] constexpr bool VariableCabEligible() const {
        return value & mask::VariableCabEligible;
    }

    // InvertedBook
    [[nodiscard]] constexpr bool InvertedBook() const {
        return value & mask::InvertedBook;
    }

    // IsAoNInstrument
    [[nodiscard]] constexpr bool IsAonInstrument() const {
        return value & mask::IsAonInstrument;
    }

    // SEFRegulated
    [[nodiscard]] constexpr bool SefRegulated() const {
        return value & mask::SefRegulated;
    }

    // MTFRegulated
    [[nodiscard]] constexpr bool MtfRegulated() const {
        return value & mask::MtfRegulated;
    }

    // eFIXInstrument
    [[nodiscard]] constexpr bool EfixInstrument() const {
        return value & mask::EfixInstrument;
    }

    // HedgeInstrument
    [[nodiscard]] constexpr bool HedgeInstrument() const {
        return value & mask::HedgeInstrument;
    }

    // 4 reserved bits
    [[nodiscard]] constexpr bool Reserved4() const {
        return value & mask::Reserved4;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
