#include "FinancialProduct.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

std::string_view to_string(FinancialProduct value) {
    switch (value) {
        case FinancialProduct::Option: return "Option";
        case FinancialProduct::Forward: return "Forward";
        case FinancialProduct::Future: return "Future";
        case FinancialProduct::Fra: return "Fra";
        case FinancialProduct::Cash: return "Cash";
        case FinancialProduct::Payment: return "Payment";
        case FinancialProduct::ExchangeRate: return "Exchange Rate";
        case FinancialProduct::InterestRateSwap: return "Interest Rate Swap";
        case FinancialProduct::Repo: return "Repo";
        case FinancialProduct::SyntheticBoxLegOrReference: return "Synthetic Box Leg Or Reference";
        case FinancialProduct::Combination: return "Combination";
        case FinancialProduct::Guarantee: return "Guarantee";
        case FinancialProduct::OtcGeneral: return "Otc General";
        case FinancialProduct::EquityWarrant: return "Equity Warrant";
        case FinancialProduct::SecurityLending: return "Security Lending";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, FinancialProduct value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
