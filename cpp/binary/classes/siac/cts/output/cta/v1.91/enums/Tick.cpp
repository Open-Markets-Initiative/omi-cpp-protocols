#include "Tick.hpp"

namespace siac::cts::output::cta::v1_91 {

std::string_view to_string(Tick value) {
    switch (value) {
        case Tick::NotApplicable: return "Not Applicable";
        case Tick::Upward: return "Upward";
        case Tick::Downward: return "Downward";
        case Tick::UnchangedUpward: return "Unchanged Upward";
        case Tick::UnchangedDownward: return "Unchanged Downward";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Tick value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v1_91
