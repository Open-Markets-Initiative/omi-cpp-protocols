#include "MdEntryType.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

std::string_view to_string(MdEntryType value) {
    switch (value) {
        case MdEntryType::Trade: return "Trade";
        case MdEntryType::OpeningPrice: return "Opening Price";
        case MdEntryType::ClosingPrice: return "Closing Price";
        case MdEntryType::HighPrice: return "High Price";
        case MdEntryType::LowPrice: return "Low Price";
        case MdEntryType::PreviousClosingPrice: return "Previous Closing Price";
        case MdEntryType::OpeningAuction: return "Opening Auction";
        case MdEntryType::IntradayAuction: return "Intraday Auction";
        case MdEntryType::CircuitBreakerAuction: return "Circuit Breaker Auction";
        case MdEntryType::ClosingAuction: return "Closing Auction";
        case MdEntryType::UpperCktLimit: return "Upper Ckt Limit";
        case MdEntryType::LowerCktLimit: return "Lower Ckt Limit";
        case MdEntryType::GrossTradeAmt: return "Gross Trade Amt";
        case MdEntryType::UpperExecLimit: return "Upper Exec Limit";
        case MdEntryType::LowerExecLimit: return "Lower Exec Limit";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MdEntryType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
