#include "MdEntryType.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

std::string_view to_string(MdEntryType value) {
    switch (value) {
        case MdEntryType::Bid: return "Bid";
        case MdEntryType::Offer: return "Offer";
        case MdEntryType::Trade: return "Trade";
        case MdEntryType::OpeningPrice: return "Opening Price";
        case MdEntryType::SettlementPrice: return "Settlement Price";
        case MdEntryType::TradingSessionHighPrice: return "Trading Session High Price";
        case MdEntryType::TradingSessionLowPrice: return "Trading Session Low Price";
        case MdEntryType::TradeVolume: return "Trade Volume";
        case MdEntryType::OpenInterest: return "Open Interest";
        case MdEntryType::ImpliedBid: return "Implied Bid";
        case MdEntryType::ImpliedOffer: return "Implied Offer";
        case MdEntryType::EmptyBook: return "Empty Book";
        case MdEntryType::SessionHighBid: return "Session High Bid";
        case MdEntryType::SessionLowOffer: return "Session Low Offer";
        case MdEntryType::FixingPrice: return "Fixing Price";
        case MdEntryType::ElectronicVolume: return "Electronic Volume";
        case MdEntryType::ThresholdLimitsandPriceBandVariation: return "Threshold Limitsand Price Band Variation";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MdEntryType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cme::globex::mdp3::sbe::v1_5
