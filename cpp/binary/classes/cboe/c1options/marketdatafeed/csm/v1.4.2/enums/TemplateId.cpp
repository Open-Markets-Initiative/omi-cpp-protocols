#include "TemplateId.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

std::string_view to_string(TemplateId value) {
    switch (value) {
        case TemplateId::SecurityDefinitionMessage: return "Security Definition Message";
        case TemplateId::CurrentMarketRefreshMessage: return "Current Market Refresh Message";
        case TemplateId::MarketDataRefreshMessage: return "Market Data Refresh Message";
        case TemplateId::CurrentMarketUpdateMessage: return "Current Market Update Message";
        case TemplateId::RecapUpdateMessage: return "Recap Update Message";
        case TemplateId::TickerMessage: return "Ticker Message";
        case TemplateId::ExpectedOpeningPriceAndSizeMessage: return "Expected Opening Price And Size Message";
        case TemplateId::IndexValueMessage: return "Index Value Message";
        case TemplateId::SettlementValueMessage: return "Settlement Value Message";
        case TemplateId::SummaryMessage: return "Summary Message";
        case TemplateId::MarketDataControlMessage: return "Market Data Control Message";
        case TemplateId::HeartbeatMessage: return "Heartbeat Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TemplateId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
