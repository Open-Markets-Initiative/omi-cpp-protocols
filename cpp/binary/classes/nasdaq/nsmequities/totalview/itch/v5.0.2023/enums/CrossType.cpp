#include "CrossType.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(CrossType value) {
    switch (value) {
        case CrossType::Opening: return "Opening";
        case CrossType::Closing: return "Closing";
        case CrossType::HaltedOrPaused: return "Halted Or Paused";
        case CrossType::ExtendedClose: return "Extended Close";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CrossType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
