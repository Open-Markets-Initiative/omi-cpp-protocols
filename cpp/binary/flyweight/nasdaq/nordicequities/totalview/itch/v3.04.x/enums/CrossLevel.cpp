#include "CrossLevel.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

std::string_view to_string(CrossLevel value) {
    switch (value) {
        case CrossLevel::Buy: return "Buy";
        case CrossLevel::Sell: return "Sell";
        case CrossLevel::Mid: return "Mid";
        case CrossLevel::Limit: return "Limit";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CrossLevel value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
