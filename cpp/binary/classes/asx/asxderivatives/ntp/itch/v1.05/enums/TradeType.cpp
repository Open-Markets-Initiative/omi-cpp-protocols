#include "TradeType.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

std::string_view to_string(TradeType value) {
    switch (value) {
        case TradeType::NormalTrade: return "Normal Trade";
        case TradeType::NormalCross: return "Normal Cross";
        case TradeType::AuctionTrade: return "Auction Trade";
        case TradeType::AuctionCross: return "Auction Cross";
        case TradeType::CombinationToUnderlyingTrade: return "Combination To Underlying Trade";
        case TradeType::CombinationToUnderlyingCross: return "Combination To Underlying Cross";
        case TradeType::CombinationToCombinationTrade: return "Combination To Combination Trade";
        case TradeType::CombinationToCombinationCross: return "Combination To Combination Cross";
        case TradeType::StripToStripTrade: return "Strip To Strip Trade";
        case TradeType::StripToStripCross: return "Strip To Strip Cross";
        case TradeType::StripToOutrightTrade: return "Strip To Outright Trade";
        case TradeType::StripToOutrightCross: return "Strip To Outright Cross";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
