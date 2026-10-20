#include "MdEntryType.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

std::string_view to_string(MdEntryType value) {
    switch (value) {
        case MdEntryType::Bid: return "Bid";
        case MdEntryType::Offer: return "Offer";
        case MdEntryType::Trade: return "Trade";
        case MdEntryType::IndexValue: return "Index Value";
        case MdEntryType::OpeningPrice: return "Opening Price";
        case MdEntryType::ClosingPrice: return "Closing Price";
        case MdEntryType::SettlementPrice: return "Settlement Price";
        case MdEntryType::SessionHighPrice: return "Session High Price";
        case MdEntryType::SessionLowPrice: return "Session Low Price";
        case MdEntryType::ExecutionStatistics: return "Execution Statistics";
        case MdEntryType::Imbalance: return "Imbalance";
        case MdEntryType::TradeVolume: return "Trade Volume";
        case MdEntryType::OpenInterest: return "Open Interest";
        case MdEntryType::EmptyBook: return "Empty Book";
        case MdEntryType::SecurityTradingStatePhase: return "Security Trading State Phase";
        case MdEntryType::PriceBand: return "Price Band";
        case MdEntryType::QuantityBand: return "Quantity Band";
        case MdEntryType::CompositeUnderlyingPrice: return "Composite Underlying Price";
        case MdEntryType::ExecutionSummary: return "Execution Summary";
        case MdEntryType::VolatilityPrice: return "Volatility Price";
        case MdEntryType::TradeBust: return "Trade Bust";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MdEntryType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
