// OtcMarkets.LinkAts.Multicast.Link.v4.3: bitfields/ExtendedSecurityFlags.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Notes security level attributes
struct ExtendedSecurityFlags {

    // underlying type
    using type = std::uint16_t;

    static constexpr const char* name = "Extended Security Flags";
    static constexpr std::size_t size = 2;

    struct mask {
        static const type Piggyback = 0x0001;
        static const type CaveatEmptorWarning = 0x0002;
        static const type QualifiedInstitutionalBuyersOnly = 0x0004;
        static const type UnsolicitedOnly = 0x0008;
        static const type SponsoredStatus = 0x0010;
        static const type OtcLinkEcnEligible = 0x0020;
        static const type OtcLinkMessagingDisabled = 0x0040;
        static const type SaturationEligible = 0x0080;
        static const type InvestmentGrade = 0x0100;
        static const type TradingFlat = 0x0200;
        static const type Callable = 0x0400;
    };

    // default constructor
    constexpr ExtendedSecurityFlags()
     : value{ 0 } {}

    // Rule 15c2-11 “Piggyback” exempt security status flag.
    [[nodiscard]] constexpr bool Piggyback() const {
        return std::byteswap(value) & mask::Piggyback;
    }

    // Indicates whether a Caveat Emptor warning has been applied to the security.
    [[nodiscard]] constexpr bool CaveatEmptorWarning() const {
        return std::byteswap(value) & mask::CaveatEmptorWarning;
    }

    // Indicates if the security may only be quoted unsolicited for Qualified Institutional Buyers.
    [[nodiscard]] constexpr bool QualifiedInstitutionalBuyersOnly() const {
        return std::byteswap(value) & mask::QualifiedInstitutionalBuyersOnly;
    }

    // Indicates if the security may only be quoted unsolicited.
    [[nodiscard]] constexpr bool UnsolicitedOnly() const {
        return std::byteswap(value) & mask::UnsolicitedOnly;
    }

    // Security is sponsored
    [[nodiscard]] constexpr bool SponsoredStatus() const {
        return std::byteswap(value) & mask::SponsoredStatus;
    }

    // Indicates if the security is eligible for OTC Link ECN.
    [[nodiscard]] constexpr bool OtcLinkEcnEligible() const {
        return std::byteswap(value) & mask::OtcLinkEcnEligible;
    }

    // Indicates whether OTC Link messaging is disabled for the security.
    [[nodiscard]] constexpr bool OtcLinkMessagingDisabled() const {
        return std::byteswap(value) & mask::OtcLinkMessagingDisabled;
    }

    // Indicates if a security is eligible to have their quotes saturated.
    [[nodiscard]] constexpr bool SaturationEligible() const {
        return std::byteswap(value) & mask::SaturationEligible;
    }

    // Security is investment grade
    [[nodiscard]] constexpr bool InvestmentGrade() const {
        return std::byteswap(value) & mask::InvestmentGrade;
    }

    // Security is trading flat
    [[nodiscard]] constexpr bool TradingFlat() const {
        return std::byteswap(value) & mask::TradingFlat;
    }

    // Security is callable
    [[nodiscard]] constexpr bool Callable() const {
        return std::byteswap(value) & mask::Callable;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
