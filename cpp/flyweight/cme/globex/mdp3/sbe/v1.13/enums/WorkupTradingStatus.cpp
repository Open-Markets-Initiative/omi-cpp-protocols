#include "WorkupTradingStatus.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

std::string_view to_string(WorkupTradingStatus value) {
    switch (value) {
        case WorkupTradingStatus::ReadyToTrade: return "Ready To Trade";
        case WorkupTradingStatus::NotAvailableForTrading: return "Not Available For Trading";
        case WorkupTradingStatus::PrivateWorkup: return "Private Workup";
        case WorkupTradingStatus::PublicWorkup: return "Public Workup";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, WorkupTradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_13
