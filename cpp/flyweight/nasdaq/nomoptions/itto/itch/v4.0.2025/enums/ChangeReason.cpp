#include "ChangeReason.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

std::string_view to_string(ChangeReason value) {
    switch (value) {
        case ChangeReason::User: return "User";
        case ChangeReason::Reprice: return "Reprice";
        case ChangeReason::Suspend: return "Suspend";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ChangeReason value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
