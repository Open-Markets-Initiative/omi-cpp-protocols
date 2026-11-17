// Databento.MarketData.Normalized.Dbn.v3: enums/InstrumentClass.cpp
#include "InstrumentClass.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

std::string_view to_string(InstrumentClass value) {
    switch (value) {
        case InstrumentClass::Bond: return "Bond";
        case InstrumentClass::Call: return "Call";
        case InstrumentClass::Future: return "Future";
        case InstrumentClass::Index: return "Index";
        case InstrumentClass::Stock: return "Stock";
        case InstrumentClass::MixedSpread: return "Mixed Spread";
        case InstrumentClass::Put: return "Put";
        case InstrumentClass::FutureSpread: return "Future Spread";
        case InstrumentClass::OptionSpread: return "Option Spread";
        case InstrumentClass::FxSpot: return "Fx Spot";
        case InstrumentClass::CommoditySpot: return "Commodity Spot";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, InstrumentClass value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace databento::marketdata::normalized::dbn::v3
