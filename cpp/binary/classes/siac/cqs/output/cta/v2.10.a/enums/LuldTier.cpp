#include "LuldTier.hpp"

namespace siac::cqs::output::cta::v2_10_a {

std::string_view to_string(LuldTier value) {
    switch (value) {
        case LuldTier::LuldNotApplicable: return "Luld Not Applicable";
        case LuldTier::LuldTier1Security: return "Luld Tier 1 Security";
        case LuldTier::LuldTier2Security: return "Luld Tier 2 Security";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LuldTier value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v2_10_a
