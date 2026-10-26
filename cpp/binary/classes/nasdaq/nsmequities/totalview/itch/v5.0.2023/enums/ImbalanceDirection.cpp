#include "ImbalanceDirection.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(ImbalanceDirection value) {
    switch (value) {
        case ImbalanceDirection::Buy: return "Buy";
        case ImbalanceDirection::Sell: return "Sell";
        case ImbalanceDirection::None: return "None";
        case ImbalanceDirection::InsufficientOrders: return "Insufficient Orders";
        case ImbalanceDirection::Paused: return "Paused";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ImbalanceDirection value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
