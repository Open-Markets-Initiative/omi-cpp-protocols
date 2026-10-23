#include "OpenCloseSettlFlag.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

std::string_view to_string(OpenCloseSettlFlag value) {
    switch (value) {
        case OpenCloseSettlFlag::DailyOpenPrice: return "Daily Open Price";
        case OpenCloseSettlFlag::IndicativeOpeningPrice: return "Indicative Opening Price";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OpenCloseSettlFlag value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_9
