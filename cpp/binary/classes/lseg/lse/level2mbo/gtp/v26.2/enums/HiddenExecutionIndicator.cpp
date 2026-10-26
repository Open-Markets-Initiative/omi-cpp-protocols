#include "HiddenExecutionIndicator.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

std::string_view to_string(HiddenExecutionIndicator value) {
    switch (value) {
        case HiddenExecutionIndicator::Na: return "Na";
        case HiddenExecutionIndicator::Visible: return "Visible";
        case HiddenExecutionIndicator::Hidden: return "Hidden";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, HiddenExecutionIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
