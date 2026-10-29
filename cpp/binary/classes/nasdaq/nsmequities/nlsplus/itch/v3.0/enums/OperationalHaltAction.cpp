#include "OperationalHaltAction.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(OperationalHaltAction value) {
    switch (value) {
        case OperationalHaltAction::Halted: return "Halted";
        case OperationalHaltAction::Trading: return "Trading";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OperationalHaltAction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
