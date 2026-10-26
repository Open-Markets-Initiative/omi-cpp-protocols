#include "Tick.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(Tick value) {
    switch (value) {
        case Tick::TickNotApplicable: return "Tick Not Applicable";
        case Tick::UpTick: return "Up Tick";
        case Tick::DownTick: return "Down Tick";
        case Tick::ZeroUpTick: return "Zero Up Tick";
        case Tick::ZeroDownTick: return "Zero Down Tick";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Tick value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
