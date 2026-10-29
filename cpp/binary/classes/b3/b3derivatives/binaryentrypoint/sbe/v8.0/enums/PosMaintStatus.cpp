#include "PosMaintStatus.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

std::string_view to_string(PosMaintStatus value) {
    switch (value) {
        case PosMaintStatus::Accepted: return "Accepted";
        case PosMaintStatus::Rejected: return "Rejected";
        case PosMaintStatus::Completed: return "Completed";
        case PosMaintStatus::NotExecuted: return "Not Executed";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PosMaintStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
