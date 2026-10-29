#include "AllocTransType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(AllocTransType value) {
    switch (value) {
        case AllocTransType::New: return "New";
        case AllocTransType::Cancel: return "Cancel";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AllocTransType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
