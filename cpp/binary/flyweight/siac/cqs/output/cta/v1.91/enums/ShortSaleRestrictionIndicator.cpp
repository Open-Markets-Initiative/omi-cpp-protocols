#include "ShortSaleRestrictionIndicator.hpp"

namespace siac::cqs::output::cta::v1_91 {

std::string_view to_string(ShortSaleRestrictionIndicator value) {
    switch (value) {
        case ShortSaleRestrictionIndicator::NotInEffect: return "Not In Effect";
        case ShortSaleRestrictionIndicator::ShortSaleRestrictionActivated: return "Short Sale Restriction Activated";
        case ShortSaleRestrictionIndicator::ShortSaleRestrictionContinued: return "Short Sale Restriction Continued";
        case ShortSaleRestrictionIndicator::ShortSaleRestrictionDeactivated: return "Short Sale Restriction Deactivated";
        case ShortSaleRestrictionIndicator::ShortSaleRestrictionInEffect: return "Short Sale Restriction In Effect";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ShortSaleRestrictionIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v1_91
