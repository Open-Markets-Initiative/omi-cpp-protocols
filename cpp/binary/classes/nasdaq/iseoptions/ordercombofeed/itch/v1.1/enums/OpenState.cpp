#include "OpenState.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

std::string_view to_string(OpenState value) {
    switch (value) {
        case OpenState::OpenForAutoExecution: return "Open For Auto Execution";
        case OpenState::ClosedForAutoExecution: return "Closed For Auto Execution";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OpenState value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
