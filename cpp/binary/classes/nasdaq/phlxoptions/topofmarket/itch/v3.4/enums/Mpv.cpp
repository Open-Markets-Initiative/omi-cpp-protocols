#include "Mpv.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

std::string_view to_string(Mpv value) {
    switch (value) {
        case Mpv::PennyEverywhere: return "Penny Everywhere";
        case Mpv::Scaled: return "Scaled";
        case Mpv::PennyPilot: return "Penny Pilot";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Mpv value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
