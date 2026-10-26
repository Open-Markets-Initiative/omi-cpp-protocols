#include "OptionsClosingType.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

std::string_view to_string(OptionsClosingType value) {
    switch (value) {
        case OptionsClosingType::Normal: return "Normal";
        case OptionsClosingType::Late: return "Late";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OptionsClosingType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
