#include "EventCode.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

std::string_view to_string(EventCode value) {
    switch (value) {
        case EventCode::EndOfDay: return "End Of Day";
        case EventCode::StartOfDay: return "Start Of Day";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, EventCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace lseg::millennium::level2::mitch::v11_9
