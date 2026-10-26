#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v13_0 {

enum class TrdType : std::uint16_t {
    BlockTrade = 1,                         // Block Trade
    Efp = 2,                                // Efp
    Efs = 12,                               // Efs
    Otc = 54,                               // Otc
    ExchangeBasisFacility = 55,             // Exchange Basis Facility
    VolaTrade = 1000,                       // Vola Trade
    EfpFinTrade = 1001,                     // Efp Fin Trade
    EfpIndexFuturesTrade = 1002,            // Efp Index Futures Trade
    BlockTradeAtMarket = 1004,              // Block Trade At Market
    XetraEurexEnlightTriggeredTrade = 1006, // Xetra Eurex Enlight Triggered Trade
    BlockQtpipTrade = 1007,                 // Block Qtpip Trade
    DeltaTradeAtMarket = 1017,              // Delta Trade At Market
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TrdType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TrdType value);

} // namespace eurex::t7::eobi::fbe::v13_0
