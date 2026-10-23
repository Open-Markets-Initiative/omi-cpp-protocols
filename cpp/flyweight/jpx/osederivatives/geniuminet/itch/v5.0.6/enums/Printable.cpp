#include "Printable.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

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

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
