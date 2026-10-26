#include "AggressingSide.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

std::string_view to_string(AggressingSide value) {
    switch (value) {
        case AggressingSide::Buy: return "Buy";
        case AggressingSide::Sell: return "Sell";
        case AggressingSide::None: return "None";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AggressingSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
