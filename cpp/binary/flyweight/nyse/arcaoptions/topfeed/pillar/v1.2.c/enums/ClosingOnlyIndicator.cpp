#include "ClosingOnlyIndicator.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

std::string_view to_string(ClosingOnlyIndicator value) {
    switch (value) {
        case ClosingOnlyIndicator::StandardSeries: return "Standard Series";
        case ClosingOnlyIndicator::Call: return "Call";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ClosingOnlyIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
