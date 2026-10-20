#include "Printable.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(Printable value) {
    switch (value) {
        case Printable::No: return "No";
        case Printable::Yes: return "Yes";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Printable value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
