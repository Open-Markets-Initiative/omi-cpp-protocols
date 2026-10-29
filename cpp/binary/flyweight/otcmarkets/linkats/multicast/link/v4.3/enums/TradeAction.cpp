#include "TradeAction.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

std::string_view to_string(TradeAction value) {
    switch (value) {
        case TradeAction::Add: return "Add";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeAction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
