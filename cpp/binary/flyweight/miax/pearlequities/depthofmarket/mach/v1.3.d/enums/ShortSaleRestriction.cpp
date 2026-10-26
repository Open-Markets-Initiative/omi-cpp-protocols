#include "ShortSaleRestriction.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

std::string_view to_string(ShortSaleRestriction value) {
    switch (value) {
        case ShortSaleRestriction::ShortSaleRestrictionIsInEffect: return "Short Sale Restriction Is In Effect";
        case ShortSaleRestriction::ShortSaleRestrictionIsNotInEffect: return "Short Sale Restriction Is Not In Effect";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ShortSaleRestriction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
