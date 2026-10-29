#include "CxlRejResponseTo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

std::string_view to_string(CxlRejResponseTo value) {
    switch (value) {
        case CxlRejResponseTo::New: return "New";
        case CxlRejResponseTo::Cancel: return "Cancel";
        case CxlRejResponseTo::Replace: return "Replace";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CxlRejResponseTo value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
