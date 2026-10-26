#include "InstrumentScopeProductComplex.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

std::string_view to_string(InstrumentScopeProductComplex value) {
    switch (value) {
        case InstrumentScopeProductComplex::SimpleInstrument: return "Simple Instrument";
        case InstrumentScopeProductComplex::StandardOptionStrategy: return "Standard Option Strategy";
        case InstrumentScopeProductComplex::NonStandardOptionStrategy: return "Non Standard Option Strategy";
        case InstrumentScopeProductComplex::VolatilityStrategy: return "Volatility Strategy";
        case InstrumentScopeProductComplex::FuturesSpread: return "Futures Spread";
        case InstrumentScopeProductComplex::InterProductSpread: return "Inter Product Spread";
        case InstrumentScopeProductComplex::StandardFuturesStrategy: return "Standard Futures Strategy";
        case InstrumentScopeProductComplex::PackAndBundle: return "Pack And Bundle";
        case InstrumentScopeProductComplex::Strip: return "Strip";
        case InstrumentScopeProductComplex::FlexibleInstrument: return "Flexible Instrument";
        case InstrumentScopeProductComplex::CommodityStrip: return "Commodity Strip";
        case InstrumentScopeProductComplex::ScaledSimpleInstrument: return "Scaled Simple Instrument";
        case InstrumentScopeProductComplex::NonStandardVolatilityStrategy: return "Non Standard Volatility Strategy";
        case InstrumentScopeProductComplex::TotalReturnFutureStrategy: return "Total Return Future Strategy";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, InstrumentScopeProductComplex value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v15_0
