#include "FinancialStatusIndicator.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(FinancialStatusIndicator value) {
    switch (value) {
        case FinancialStatusIndicator::Deficient: return "Deficient";
        case FinancialStatusIndicator::Delinquent: return "Delinquent";
        case FinancialStatusIndicator::Bankrupt: return "Bankrupt";
        case FinancialStatusIndicator::Suspended: return "Suspended";
        case FinancialStatusIndicator::DeficientAndBankrupt: return "Deficient And Bankrupt";
        case FinancialStatusIndicator::DeficientAndDelinquent: return "Deficient And Delinquent";
        case FinancialStatusIndicator::DelinquentAndBankrupt: return "Delinquent And Bankrupt";
        case FinancialStatusIndicator::DeficientDelinquentAndBankrupt: return "Deficient Delinquent And Bankrupt";
        case FinancialStatusIndicator::CreationsAndRedemptionsSuspended: return "Creations And Redemptions Suspended";
        case FinancialStatusIndicator::Normal: return "Normal";
        case FinancialStatusIndicator::NotAvailable: return "Not Available";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, FinancialStatusIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
