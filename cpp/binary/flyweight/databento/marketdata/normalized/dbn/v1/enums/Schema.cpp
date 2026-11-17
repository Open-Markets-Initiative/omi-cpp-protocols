// Databento.MarketData.Normalized.Dbn.v1: enums/Schema.cpp
#include "Schema.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

std::string_view to_string(Schema value) {
    switch (value) {
        case Schema::Mbo: return "Mbo";
        case Schema::Mbp1: return "Mbp1";
        case Schema::Mbp10: return "Mbp10";
        case Schema::Tbbo: return "Tbbo";
        case Schema::Trades: return "Trades";
        case Schema::Ohlcv1S: return "Ohlcv1 S";
        case Schema::Ohlcv1M: return "Ohlcv1 M";
        case Schema::Ohlcv1H: return "Ohlcv1 H";
        case Schema::Ohlcv1D: return "Ohlcv1 D";
        case Schema::Definition: return "Definition";
        case Schema::Statistics: return "Statistics";
        case Schema::Status: return "Status";
        case Schema::Imbalance: return "Imbalance";
        case Schema::OhlcvEod: return "Ohlcv Eod";
        case Schema::Cmbp1: return "Cmbp1";
        case Schema::Cbbo1S: return "Cbbo1 S";
        case Schema::Cbbo1M: return "Cbbo1 M";
        case Schema::Tcbbo: return "Tcbbo";
        case Schema::Bbo1S: return "Bbo1 S";
        case Schema::Bbo1M: return "Bbo1 M";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Schema value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace databento::marketdata::normalized::dbn::v1
