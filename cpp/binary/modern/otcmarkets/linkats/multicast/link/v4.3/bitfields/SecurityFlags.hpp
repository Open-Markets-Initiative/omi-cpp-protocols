// OtcMarkets.LinkAts.Multicast.Link.v4.3: bitfields/SecurityFlags.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Notes security level attributes
struct SecurityFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Security Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type Piggyback = 0x01;
        static const type CaveatEmptorWarning = 0x02;
        static const type QualifiedInstitutionalBuyersOnly = 0x04;
        static const type UnsolicitedOnly = 0x08;
        static const type BbQuoted = 0x10;
        static const type OtcLinkEcnEligible = 0x20;
        static const type OtcLinkMessagingDisabled = 0x40;
        static const type SaturationEligible = 0x80;
    };

    // default constructor
    constexpr SecurityFlags()
     : value{ 0 } {}

    // Rule 15c2-11 “Piggyback” exempt security status flag.
    [[nodiscard]] constexpr bool Piggyback() const {
        return value & mask::Piggyback;
    }

    // Indicates whether a Caveat Emptor warning has been applied to the security.
    [[nodiscard]] constexpr bool CaveatEmptorWarning() const {
        return value & mask::CaveatEmptorWarning;
    }

    // Indicates if the security may only be quoted unsolicited for Qualified Institutional Buyers.
    [[nodiscard]] constexpr bool QualifiedInstitutionalBuyersOnly() const {
        return value & mask::QualifiedInstitutionalBuyersOnly;
    }

    // Indicates if the security may only be quoted unsolicited.
    [[nodiscard]] constexpr bool UnsolicitedOnly() const {
        return value & mask::UnsolicitedOnly;
    }

    // Indicates if the security is quoted on the OTC Bulletin Board interdealer quotation system.
    [[nodiscard]] constexpr bool BbQuoted() const {
        return value & mask::BbQuoted;
    }

    // Indicates if the security is eligible for OTC Link ECN.
    [[nodiscard]] constexpr bool OtcLinkEcnEligible() const {
        return value & mask::OtcLinkEcnEligible;
    }

    // Indicates whether OTC Link messaging is disabled for the security.
    [[nodiscard]] constexpr bool OtcLinkMessagingDisabled() const {
        return value & mask::OtcLinkMessagingDisabled;
    }

    // Indicates if a security is eligible to have their quotes saturated.
    [[nodiscard]] constexpr bool SaturationEligible() const {
        return value & mask::SaturationEligible;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
