// Nasdaq.NomOptions.Itto.Itch.v4.0.2025: enums/Tradable.cpp
#include "Tradable.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

std::string_view to_string(Tradable value) {
    switch (value) {
        case Tradable::NotTradable: return "Not Tradable";
        case Tradable::IsTradable: return "Is Tradable";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Tradable value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
