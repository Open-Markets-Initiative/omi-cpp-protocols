#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::c1options::complex::pitch::v2_1_18 {

// Options Only (byte not sent in Equities) (Space): Normal Trade S: Spread trade
enum class TradeCondition : char {
    ComplexToComplexElectronicTrade = 'f',     // Complex To Complex Electronic Trade
    ComplexAuctionTrade = 'g',                 // Complex Auction Trade
    ComplexCross = 'h',                        // Complex Cross
    ComplexElectronicTradeAgainstSingle = 'j', // Complex Electronic Trade Against Single
    ComplexWithStockOptionsAuctionTrade = 'k', // Complex With Stock Options Auction Trade
    ComplexWithStockElectronicTrade = 'n',     // Complex With Stock Electronic Trade
    ComplexWithStockCross = 'o',               // Complex With Stock Cross
    ElectronicTrade = 'I',                     // Electronic Trade
    OpeningTrade = 'O',                        // Opening Trade
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeCondition value);

} // namespace cboe::c1options::complex::pitch::v2_1_18
