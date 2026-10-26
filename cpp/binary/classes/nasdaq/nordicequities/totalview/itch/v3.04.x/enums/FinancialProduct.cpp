#include "FinancialProduct.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

std::string_view to_string(FinancialProduct value) {
    switch (value) {
        case FinancialProduct::Stock: return "Stock";
        case FinancialProduct::EquityWarrant: return "Equity Warrant";
        case FinancialProduct::EquityRight: return "Equity Right";
        case FinancialProduct::Bond: return "Bond";
        case FinancialProduct::LotteryBondSeries: return "Lottery Bond Series";
        case FinancialProduct::Convertible: return "Convertible";
        case FinancialProduct::Warrant: return "Warrant";
        case FinancialProduct::UnitTrustCertificate: return "Unit Trust Certificate";
        case FinancialProduct::IndexFundUnit: return "Index Fund Unit";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, FinancialProduct value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
