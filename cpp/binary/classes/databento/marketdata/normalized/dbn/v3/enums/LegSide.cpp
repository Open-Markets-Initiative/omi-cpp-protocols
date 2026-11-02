#include "LegSide.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

std::string_view to_string(LegSide value) {
    switch (value) {
        case LegSide::Ask: return "Ask";
        case LegSide::Bid: return "Bid";
        case LegSide::None: return "None";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LegSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace databento::marketdata::normalized::dbn::v3
