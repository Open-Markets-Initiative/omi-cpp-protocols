#include "MassActionResponse.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

std::string_view to_string(MassActionResponse value) {
    switch (value) {
        case MassActionResponse::Rejected: return "Rejected";
        case MassActionResponse::Accepted: return "Accepted";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MassActionResponse value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
