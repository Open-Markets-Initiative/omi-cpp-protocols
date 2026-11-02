#include "SecurityUpdateAction.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

std::string_view to_string(SecurityUpdateAction value) {
    switch (value) {
        case SecurityUpdateAction::Add: return "Add";
        case SecurityUpdateAction::Delete: return "Delete";
        case SecurityUpdateAction::Modify: return "Modify";
        case SecurityUpdateAction::Invalid: return "Invalid";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityUpdateAction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace databento::marketdata::normalized::dbn::v2
