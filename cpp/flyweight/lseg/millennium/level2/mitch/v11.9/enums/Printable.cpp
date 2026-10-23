#include "Printable.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

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

} // namespace lseg::millennium::level2::mitch::v11_9
