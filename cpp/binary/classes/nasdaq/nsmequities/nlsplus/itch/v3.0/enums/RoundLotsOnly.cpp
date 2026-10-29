#include "RoundLotsOnly.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(RoundLotsOnly value) {
    switch (value) {
        case RoundLotsOnly::RoundLotsOnly: return "Round Lots Only";
        case RoundLotsOnly::NoRestriction: return "No Restriction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RoundLotsOnly value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
