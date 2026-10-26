#include "RoundLotsOnly.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

std::string_view to_string(RoundLotsOnly value) {
    switch (value) {
        case RoundLotsOnly::RoundLotsOnly: return "Round Lots Only";
        case RoundLotsOnly::NoRestrictions: return "No Restrictions";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RoundLotsOnly value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
