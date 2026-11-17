// Databento.MarketData.Normalized.Dbn.v3: enums/LegInstrumentClass.cpp
#include "LegInstrumentClass.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

std::string_view to_string(LegInstrumentClass value) {
    switch (value) {
        case LegInstrumentClass::Bond: return "Bond";
        case LegInstrumentClass::Call: return "Call";
        case LegInstrumentClass::Future: return "Future";
        case LegInstrumentClass::Index: return "Index";
        case LegInstrumentClass::Stock: return "Stock";
        case LegInstrumentClass::MixedSpread: return "Mixed Spread";
        case LegInstrumentClass::Put: return "Put";
        case LegInstrumentClass::FutureSpread: return "Future Spread";
        case LegInstrumentClass::OptionSpread: return "Option Spread";
        case LegInstrumentClass::FxSpot: return "Fx Spot";
        case LegInstrumentClass::CommoditySpot: return "Commodity Spot";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LegInstrumentClass value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace databento::marketdata::normalized::dbn::v3
