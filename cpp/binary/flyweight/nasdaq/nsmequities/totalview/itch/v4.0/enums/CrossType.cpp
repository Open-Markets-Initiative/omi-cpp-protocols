#include "CrossType.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

std::string_view to_string(CrossType value) {
    switch (value) {
        case CrossType::Opening: return "Opening";
        case CrossType::Closing: return "Closing";
        case CrossType::IpoAndHalted: return "Ipo And Halted";
        case CrossType::CrossNetwork: return "Cross Network";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CrossType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
