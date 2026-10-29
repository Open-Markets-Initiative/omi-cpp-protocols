#include "InsideAction.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

std::string_view to_string(InsideAction value) {
    switch (value) {
        case InsideAction::Add: return "Add";
        case InsideAction::Delete: return "Delete";
        case InsideAction::Spin: return "Spin";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, InsideAction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
