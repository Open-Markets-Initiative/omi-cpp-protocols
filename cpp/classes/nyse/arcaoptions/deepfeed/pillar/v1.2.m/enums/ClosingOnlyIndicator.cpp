#include "ClosingOnlyIndicator.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

std::string_view to_string(ClosingOnlyIndicator value) {
    switch (value) {
        case ClosingOnlyIndicator::StandardSeries: return "Standard Series";
        case ClosingOnlyIndicator::ClosingOnlySeries: return "Closing Only Series";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ClosingOnlyIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
