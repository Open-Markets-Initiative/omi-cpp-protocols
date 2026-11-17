// Databento.MarketData.Normalized.Dbn.v3: enums/Rtype.cpp
#include "Rtype.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

std::string_view to_string(Rtype value) {
    switch (value) {
        case Rtype::MarketByPrice0: return "Market By Price 0";
        case Rtype::MarketByPrice1: return "Market By Price 1";
        case Rtype::MarketByPrice10: return "Market By Price 10";
        case Rtype::OhlcvDeprecated: return "Ohlcv Deprecated";
        case Rtype::Status: return "Status";
        case Rtype::InstrumentDefinition: return "Instrument Definition";
        case Rtype::Imbalance: return "Imbalance";
        case Rtype::Error: return "Error";
        case Rtype::SymbolMapping: return "Symbol Mapping";
        case Rtype::System: return "System";
        case Rtype::Statistics: return "Statistics";
        case Rtype::Ohlcv1Second: return "Ohlcv 1 Second";
        case Rtype::Ohlcv1Minute: return "Ohlcv 1 Minute";
        case Rtype::Ohlcv1Hour: return "Ohlcv 1 Hour";
        case Rtype::Ohlcv1Day: return "Ohlcv 1 Day";
        case Rtype::OhlcvEndOfDay: return "Ohlcv End Of Day";
        case Rtype::MarketByOrder: return "Market By Order";
        case Rtype::ConsolidatedMarketByPrice1: return "Consolidated Market By Price 1";
        case Rtype::ConsolidatedBbo1Second: return "Consolidated Bbo 1 Second";
        case Rtype::ConsolidatedBbo1Minute: return "Consolidated Bbo 1 Minute";
        case Rtype::TradeWithConsolidatedBbo: return "Trade With Consolidated Bbo";
        case Rtype::Bbo1Second: return "Bbo 1 Second";
        case Rtype::Bbo1Minute: return "Bbo 1 Minute";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Rtype value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace databento::marketdata::normalized::dbn::v3
