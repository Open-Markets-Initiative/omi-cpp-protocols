#include "RegShoAction.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(RegShoAction value) {
    switch (value) {
        case RegShoAction::NoPriceTest: return "No Price Test";
        case RegShoAction::RegShoShortSalePriceTestRestriction: return "Reg Sho Short Sale Price Test Restriction";
        case RegShoAction::TestRestrictionRemains: return "Test Restriction Remains";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RegShoAction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
