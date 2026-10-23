#include "Printable.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

std::string_view to_string(Printable value) {
    switch (value) {
        case Printable::NonPrintable: return "Non Printable";
        case Printable::Printable: return "Printable";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Printable value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
