#include "OptionClosingType.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

std::string_view to_string(OptionClosingType value) {
    switch (value) {
        case OptionClosingType::Normal: return "Normal";
        case OptionClosingType::Late: return "Late";
        case OptionClosingType::WcoEarlyClosing: return "Wco Early Closing";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OptionClosingType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
