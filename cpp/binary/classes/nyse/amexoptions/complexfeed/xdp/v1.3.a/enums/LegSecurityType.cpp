#include "LegSecurityType.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

std::string_view to_string(LegSecurityType value) {
    switch (value) {
        case LegSecurityType::OptionsSeriesLeg: return "Options Series Leg";
        case LegSecurityType::EquityStockLeg: return "Equity Stock Leg";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LegSecurityType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
