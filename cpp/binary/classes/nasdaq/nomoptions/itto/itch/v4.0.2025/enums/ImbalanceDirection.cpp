#include "ImbalanceDirection.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

std::string_view to_string(ImbalanceDirection value) {
    switch (value) {
        case ImbalanceDirection::Buy: return "Buy";
        case ImbalanceDirection::Sell: return "Sell";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ImbalanceDirection value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
