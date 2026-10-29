#include "CancelErrorAction.hpp"

namespace siac::cts::output::cta::v2_9 {

std::string_view to_string(CancelErrorAction value) {
    switch (value) {
        case CancelErrorAction::Cancel: return "Cancel";
        case CancelErrorAction::Error: return "Error";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CancelErrorAction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_9
