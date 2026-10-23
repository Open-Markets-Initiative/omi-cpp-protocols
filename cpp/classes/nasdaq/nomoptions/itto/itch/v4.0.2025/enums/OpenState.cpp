#include "OpenState.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

std::string_view to_string(OpenState value) {
    switch (value) {
        case OpenState::Open: return "Open";
        case OpenState::Closed: return "Closed";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OpenState value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
