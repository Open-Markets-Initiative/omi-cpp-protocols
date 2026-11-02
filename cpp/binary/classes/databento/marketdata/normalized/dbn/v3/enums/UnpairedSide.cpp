#include "UnpairedSide.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

std::string_view to_string(UnpairedSide value) {
    switch (value) {
        case UnpairedSide::Ask: return "Ask";
        case UnpairedSide::Bid: return "Bid";
        case UnpairedSide::None: return "None";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, UnpairedSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace databento::marketdata::normalized::dbn::v3
