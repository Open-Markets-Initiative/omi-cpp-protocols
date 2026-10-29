#include "TradeCond1.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

std::string_view to_string(TradeCond1 value) {
    switch (value) {
        case TradeCond1::RegularTrade: return "Regular Trade";
        case TradeCond1::LateReport: return "Late Report";
        case TradeCond1::FloorTrade: return "Floor Trade";
        case TradeCond1::SoSweepTrade: return "So Sweep Trade";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeCond1 value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
