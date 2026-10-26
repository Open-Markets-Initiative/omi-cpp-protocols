#include "LegSide.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

std::string_view to_string(LegSide value) {
    switch (value) {
        case LegSide::AsDefined: return "As Defined";
        case LegSide::Opposite: return "Opposite";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LegSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
