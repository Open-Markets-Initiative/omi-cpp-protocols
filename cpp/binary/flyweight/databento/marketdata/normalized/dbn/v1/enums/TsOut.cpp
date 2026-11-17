// Databento.MarketData.Normalized.Dbn.v1: enums/TsOut.cpp
#include "TsOut.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

std::string_view to_string(TsOut value) {
    switch (value) {
        case TsOut::No: return "No";
        case TsOut::Yes: return "Yes";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TsOut value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace databento::marketdata::normalized::dbn::v1
