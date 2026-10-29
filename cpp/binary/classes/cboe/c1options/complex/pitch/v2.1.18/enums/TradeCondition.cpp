#include "TradeCondition.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

std::string_view to_string(TradeCondition value) {
    switch (value) {
        case TradeCondition::ComplexToComplexElectronicTrade: return "Complex To Complex Electronic Trade";
        case TradeCondition::ComplexAuctionTrade: return "Complex Auction Trade";
        case TradeCondition::ComplexCross: return "Complex Cross";
        case TradeCondition::ComplexElectronicTradeAgainstSingle: return "Complex Electronic Trade Against Single";
        case TradeCondition::ComplexWithStockOptionsAuctionTrade: return "Complex With Stock Options Auction Trade";
        case TradeCondition::ComplexWithStockElectronicTrade: return "Complex With Stock Electronic Trade";
        case TradeCondition::ComplexWithStockCross: return "Complex With Stock Cross";
        case TradeCondition::ElectronicTrade: return "Electronic Trade";
        case TradeCondition::OpeningTrade: return "Opening Trade";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
