#include "RegShoAction.hpp"

namespace cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29 {

std::string_view to_string(RegShoAction value) {
    switch (value) {
        case RegShoAction::NoPriceTestInEffect: return "No Price Test In Effect";
        case RegShoAction::RegShoPriceTestRestrictionInEffect: return "Reg Sho Price Test Restriction In Effect";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RegShoAction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29
