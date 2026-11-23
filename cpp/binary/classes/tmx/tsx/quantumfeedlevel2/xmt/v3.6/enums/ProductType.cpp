// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: enums/ProductType.cpp
#include "ProductType.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

std::string_view to_string(ProductType value) {
    switch (value) {
        case ProductType::Debenture: return "Debenture";
        case ProductType::Equity: return "Equity";
        case ProductType::MutualFund: return "Mutual Fund";
        case ProductType::Etf: return "Etf";
        case ProductType::UsEquity: return "Us Equity";
        case ProductType::Bond: return "Bond";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ProductType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
