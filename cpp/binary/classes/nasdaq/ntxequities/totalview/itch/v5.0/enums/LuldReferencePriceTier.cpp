#include "LuldReferencePriceTier.hpp"

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

std::string_view to_string(LuldReferencePriceTier value) {
    switch (value) {
        case LuldReferencePriceTier::Tier1NmsStocksAndSelectEtPs: return "Tier 1 Nms Stocks And Select Et Ps";
        case LuldReferencePriceTier::Tier2NmsStocks: return "Tier 2 Nms Stocks";
        case LuldReferencePriceTier::NotAvailable: return "Not Available";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LuldReferencePriceTier value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
