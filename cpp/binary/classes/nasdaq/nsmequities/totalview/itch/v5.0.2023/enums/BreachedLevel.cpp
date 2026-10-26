#include "BreachedLevel.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(BreachedLevel value) {
    switch (value) {
        case BreachedLevel::Level1: return "Level 1";
        case BreachedLevel::Level2: return "Level 2";
        case BreachedLevel::Level3: return "Level 3";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, BreachedLevel value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
