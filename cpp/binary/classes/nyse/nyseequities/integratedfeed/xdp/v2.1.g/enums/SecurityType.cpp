#include "SecurityType.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

std::string_view to_string(SecurityType value) {
    switch (value) {
        case SecurityType::CommonStock: return "Common Stock";
        case SecurityType::PreferredStock: return "Preferred Stock";
        case SecurityType::Warrant: return "Warrant";
        case SecurityType::Right: return "Right";
        case SecurityType::CorporateBond: return "Corporate Bond";
        case SecurityType::TreasuryBond: return "Treasury Bond";
        case SecurityType::StructuredProduct: return "Structured Product";
        case SecurityType::AdrCommon: return "Adr Common";
        case SecurityType::AdrPreferred: return "Adr Preferred";
        case SecurityType::AdrWarrants: return "Adr Warrants";
        case SecurityType::AdrRights: return "Adr Rights";
        case SecurityType::AdrCorporateBond: return "Adr Corporate Bond";
        case SecurityType::NyRegisteredShare: return "Ny Registered Share";
        case SecurityType::GlobalRegisteredShare: return "Global Registered Share";
        case SecurityType::Index: return "Index";
        case SecurityType::Fund: return "Fund";
        case SecurityType::Basket: return "Basket";
        case SecurityType::Unit: return "Unit";
        case SecurityType::LiquidatingTrust: return "Liquidating Trust";
        case SecurityType::Unknown: return "Unknown";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
