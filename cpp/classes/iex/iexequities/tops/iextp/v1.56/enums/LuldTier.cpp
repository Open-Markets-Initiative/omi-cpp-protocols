#include "LuldTier.hpp"

namespace iex::iexequities::tops::iextp::v1_56 {

std::string_view to_string(LuldTier value) {
    switch (value) {
        case LuldTier::NotApplicable: return "Not Applicable";
        case LuldTier::Tier1NmsStock: return "Tier 1 Nms Stock";
        case LuldTier::Tier2NmsStock: return "Tier 2 Nms Stock";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LuldTier value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace iex::iexequities::tops::iextp::v1_56
