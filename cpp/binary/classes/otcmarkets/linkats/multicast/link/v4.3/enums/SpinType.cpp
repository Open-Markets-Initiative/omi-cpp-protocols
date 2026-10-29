#include "SpinType.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

std::string_view to_string(SpinType value) {
    switch (value) {
        case SpinType::Reference: return "Reference";
        case SpinType::MarketData: return "Market Data";
        case SpinType::Opening: return "Opening";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SpinType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
