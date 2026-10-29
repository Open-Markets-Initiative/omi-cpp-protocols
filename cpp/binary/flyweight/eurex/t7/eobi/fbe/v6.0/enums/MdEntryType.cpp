#include "MdEntryType.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

std::string_view to_string(MdEntryType value) {
    switch (value) {
        case MdEntryType::Trade: return "Trade";
        case MdEntryType::OpeningPrice: return "Opening Price";
        case MdEntryType::ClosingPrice: return "Closing Price";
        case MdEntryType::HighPrice: return "High Price";
        case MdEntryType::LowPrice: return "Low Price";
        case MdEntryType::TradeVolume: return "Trade Volume";
        case MdEntryType::PreviousClosingPrice: return "Previous Closing Price";
        case MdEntryType::OpeningAuction: return "Opening Auction";
        case MdEntryType::IntradayAuction: return "Intraday Auction";
        case MdEntryType::CircuitBreakerAuction: return "Circuit Breaker Auction";
        case MdEntryType::ClosingAuction: return "Closing Auction";
        case MdEntryType::IpoAuction: return "Ipo Auction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MdEntryType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v6_0
