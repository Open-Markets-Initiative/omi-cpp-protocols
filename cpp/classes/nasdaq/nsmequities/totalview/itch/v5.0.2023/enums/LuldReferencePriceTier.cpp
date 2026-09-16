#include "LuldReferencePriceTier.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(LuldReferencePriceTier value) {
    switch (value) {
        case LuldReferencePriceTier::Tier1: return "Tier 1";
        case LuldReferencePriceTier::Tier2: return "Tier 2";
        case LuldReferencePriceTier::NotAvailable: return "Not Available";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LuldReferencePriceTier value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
