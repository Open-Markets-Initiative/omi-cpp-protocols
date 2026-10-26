#include "RegShoAction.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

std::string_view to_string(RegShoAction value) {
    switch (value) {
        case RegShoAction::NoPriceTest: return "No Price Test";
        case RegShoAction::RestrictionInEffect: return "Restriction In Effect";
        case RegShoAction::RestrictionRemains: return "Restriction Remains";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RegShoAction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
