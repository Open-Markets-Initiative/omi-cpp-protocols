#include "ShortSaleRestrictionIndicator.hpp"

namespace siac::cts::output::cta::v1_91 {

std::string_view to_string(ShortSaleRestrictionIndicator value) {
    switch (value) {
        case ShortSaleRestrictionIndicator::NotInEffect: return "Not In Effect";
        case ShortSaleRestrictionIndicator::Activated: return "Activated";
        case ShortSaleRestrictionIndicator::Continued: return "Continued";
        case ShortSaleRestrictionIndicator::Deactivated: return "Deactivated";
        case ShortSaleRestrictionIndicator::RestrictionInEffect: return "Restriction In Effect";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ShortSaleRestrictionIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v1_91
