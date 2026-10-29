#include "CrossType.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

std::string_view to_string(CrossType value) {
    switch (value) {
        case CrossType::EarlyOpening: return "Early Opening";
        case CrossType::Opening: return "Opening";
        case CrossType::Reopening: return "Reopening";
        case CrossType::Closing: return "Closing";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CrossType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
