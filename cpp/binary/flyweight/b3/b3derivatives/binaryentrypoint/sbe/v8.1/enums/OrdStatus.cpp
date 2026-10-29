#include "OrdStatus.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

std::string_view to_string(OrdStatus value) {
    switch (value) {
        case OrdStatus::New: return "New";
        case OrdStatus::PartiallyFilled: return "Partially Filled";
        case OrdStatus::Filled: return "Filled";
        case OrdStatus::Canceled: return "Canceled";
        case OrdStatus::Replaced: return "Replaced";
        case OrdStatus::Rejected: return "Rejected";
        case OrdStatus::Expired: return "Expired";
        case OrdStatus::Restated: return "Restated";
        case OrdStatus::PreviousFinalState: return "Previous Final State";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OrdStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
