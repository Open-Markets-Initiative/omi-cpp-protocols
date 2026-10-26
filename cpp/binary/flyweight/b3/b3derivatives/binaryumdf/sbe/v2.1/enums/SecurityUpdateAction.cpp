#include "SecurityUpdateAction.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

std::string_view to_string(SecurityUpdateAction value) {
    switch (value) {
        case SecurityUpdateAction::Add: return "Add";
        case SecurityUpdateAction::Delete: return "Delete";
        case SecurityUpdateAction::Modify: return "Modify";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityUpdateAction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
