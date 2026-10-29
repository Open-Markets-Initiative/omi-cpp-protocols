#include "OpenState.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

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

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
