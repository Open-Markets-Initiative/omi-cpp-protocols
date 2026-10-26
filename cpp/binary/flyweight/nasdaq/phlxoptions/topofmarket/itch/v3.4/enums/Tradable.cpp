#include "Tradable.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

std::string_view to_string(Tradable value) {
    switch (value) {
        case Tradable::Tradable: return "Tradable";
        case Tradable::NotTradable: return "Not Tradable";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Tradable value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
