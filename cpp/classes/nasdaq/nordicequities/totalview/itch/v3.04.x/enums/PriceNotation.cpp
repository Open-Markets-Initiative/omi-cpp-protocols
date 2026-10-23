#include "PriceNotation.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

std::string_view to_string(PriceNotation value) {
    switch (value) {
        case PriceNotation::MonetaryValue: return "Monetary Value";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PriceNotation value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
