#include "StatType.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

std::string_view to_string(StatType value) {
    switch (value) {
        case StatType::OpeningPrice: return "Opening Price";
        case StatType::IndicativeOpeningPrice: return "Indicative Opening Price";
        case StatType::SettlementPrice: return "Settlement Price";
        case StatType::TradingSessionLowPrice: return "Trading Session Low Price";
        case StatType::TradingSessionHighPrice: return "Trading Session High Price";
        case StatType::ClearedVolume: return "Cleared Volume";
        case StatType::LowestOffer: return "Lowest Offer";
        case StatType::HighestBid: return "Highest Bid";
        case StatType::OpenInterest: return "Open Interest";
        case StatType::FixingPrice: return "Fixing Price";
        case StatType::ClosePrice: return "Close Price";
        case StatType::NetChange: return "Net Change";
        case StatType::Vwap: return "Vwap";
        case StatType::Volatility: return "Volatility";
        case StatType::Delta: return "Delta";
        case StatType::UncrossingPrice: return "Uncrossing Price";
        case StatType::UpperPriceLimit: return "Upper Price Limit";
        case StatType::LowerPriceLimit: return "Lower Price Limit";
        case StatType::BlockVolume: return "Block Volume";
        case StatType::IndicativeClosePrice: return "Indicative Close Price";
        case StatType::MwcbLevel1: return "Mwcb Level1";
        case StatType::MwcbLevel2: return "Mwcb Level2";
        case StatType::MwcbLevel3: return "Mwcb Level3";
        case StatType::AuctionCollarReferencePrice: return "Auction Collar Reference Price";
        case StatType::AuctionCollarUpperPrice: return "Auction Collar Upper Price";
        case StatType::AuctionCollarLowerPrice: return "Auction Collar Lower Price";
        case StatType::VenueSpecificVolume1: return "Venue Specific Volume1";
        case StatType::VenueSpecificPrice1: return "Venue Specific Price1";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, StatType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace databento::marketdata::normalized::dbn::v2
