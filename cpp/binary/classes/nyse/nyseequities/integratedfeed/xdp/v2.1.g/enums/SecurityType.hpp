#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

// Type of Security used by Arca, National and American
enum class SecurityType : char {
    CommonStock = 'A',           // Common Stock
    PreferredStock = 'B',        // Preferred Stock
    Warrant = 'C',               // Warrant
    Right = 'D',                 // Right
    CorporateBond = 'E',         // Corporate Bond
    TreasuryBond = 'F',          // Treasury Bond
    StructuredProduct = 'G',     // Structured Product
    AdrCommon = 'H',             // Adr Common
    AdrPreferred = 'I',          // Adr Preferred
    AdrWarrants = 'J',           // Adr Warrants
    AdrRights = 'K',             // Adr Rights
    AdrCorporateBond = 'L',      // Adr Corporate Bond
    NyRegisteredShare = 'M',     // Ny Registered Share
    GlobalRegisteredShare = 'N', // Global Registered Share
    Index = 'O',                 // Index
    Fund = 'P',                  // Fund
    Basket = 'Q',                // Basket
    Unit = 'R',                  // Unit
    LiquidatingTrust = 'S',      // Liquidating Trust
    Unknown = 'U',               // Unknown
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityType value);

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
