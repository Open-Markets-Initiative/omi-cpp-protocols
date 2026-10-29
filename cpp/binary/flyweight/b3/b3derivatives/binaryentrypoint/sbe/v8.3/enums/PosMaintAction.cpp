#include "PosMaintAction.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(PosMaintAction value) {
    switch (value) {
        case PosMaintAction::New: return "New";
        case PosMaintAction::Cancel: return "Cancel";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PosMaintAction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
