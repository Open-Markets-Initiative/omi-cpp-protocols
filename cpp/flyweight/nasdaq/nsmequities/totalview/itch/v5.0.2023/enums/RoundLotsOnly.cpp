#include "RoundLotsOnly.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(RoundLotsOnly value) {
    switch (value) {
        case RoundLotsOnly::Yes: return "Yes";
        case RoundLotsOnly::No: return "No";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RoundLotsOnly value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
