#include "OpenCloseSettlFlag.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

std::string_view to_string(OpenCloseSettlFlag value) {
    switch (value) {
        case OpenCloseSettlFlag::DailyOpenPrice: return "Daily Open Price";
        case OpenCloseSettlFlag::IndicativeOpeningPrice: return "Indicative Opening Price";
        case OpenCloseSettlFlag::IntradayVwap: return "Intraday Vwap";
        case OpenCloseSettlFlag::RepoAverage830Am: return "Repo Average 830 Am";
        case OpenCloseSettlFlag::RepoAverage10Am: return "Repo Average 10 Am";
        case OpenCloseSettlFlag::PrevSessionRepoAverage10Am: return "Prev Session Repo Average 10 Am";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OpenCloseSettlFlag value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_13
