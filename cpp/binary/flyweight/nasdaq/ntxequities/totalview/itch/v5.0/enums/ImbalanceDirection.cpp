#include "ImbalanceDirection.hpp"

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

std::string_view to_string(ImbalanceDirection value) {
    switch (value) {
        case ImbalanceDirection::Buy: return "Buy";
        case ImbalanceDirection::Sell: return "Sell";
        case ImbalanceDirection::NoImbalance: return "No Imbalance";
        case ImbalanceDirection::Insufficient: return "Insufficient";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ImbalanceDirection value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
