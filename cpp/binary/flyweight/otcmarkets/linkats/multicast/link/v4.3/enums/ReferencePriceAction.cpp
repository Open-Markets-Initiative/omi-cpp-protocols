#include "ReferencePriceAction.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

std::string_view to_string(ReferencePriceAction value) {
    switch (value) {
        case ReferencePriceAction::Add: return "Add";
        case ReferencePriceAction::Delete: return "Delete";
        case ReferencePriceAction::Spin: return "Spin";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ReferencePriceAction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
