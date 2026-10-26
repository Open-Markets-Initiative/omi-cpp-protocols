#include "Mpv.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

std::string_view to_string(Mpv value) {
    switch (value) {
        case Mpv::Everywhere: return "Everywhere";
        case Mpv::Scaled: return "Scaled";
        case Mpv::Pilot: return "Pilot";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Mpv value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
