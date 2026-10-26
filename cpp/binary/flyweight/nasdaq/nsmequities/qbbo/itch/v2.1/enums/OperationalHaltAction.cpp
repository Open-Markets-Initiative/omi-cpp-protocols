#include "OperationalHaltAction.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

std::string_view to_string(OperationalHaltAction value) {
    switch (value) {
        case OperationalHaltAction::Halted: return "Halted";
        case OperationalHaltAction::Resumed: return "Resumed";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OperationalHaltAction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
