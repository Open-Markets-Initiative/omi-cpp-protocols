#include "Extension.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

std::string_view to_string(Extension value) {
    switch (value) {
        case Extension::CrossExtension: return "Cross Extension";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Extension value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
