#include "SecurityAction.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

std::string_view to_string(SecurityAction value) {
    switch (value) {
        case SecurityAction::Update: return "Update";
        case SecurityAction::Add: return "Add";
        case SecurityAction::Delete: return "Delete";
        case SecurityAction::Spin: return "Spin";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityAction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
