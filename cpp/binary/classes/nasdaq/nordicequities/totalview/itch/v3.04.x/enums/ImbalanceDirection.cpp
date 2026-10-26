#include "ImbalanceDirection.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

std::string_view to_string(ImbalanceDirection value) {
    switch (value) {
        case ImbalanceDirection::BuyImbalance: return "Buy Imbalance";
        case ImbalanceDirection::SellImbalance: return "Sell Imbalance";
        case ImbalanceDirection::NoImbalance: return "No Imbalance";
        case ImbalanceDirection::InsufficientOrdersToCalculate: return "Insufficient Orders To Calculate";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ImbalanceDirection value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
