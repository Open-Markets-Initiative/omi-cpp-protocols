#include "Issue.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

std::string_view to_string(Issue value) {
    switch (value) {
        case Issue::PeriodicIndicativeSettlement: return "Periodic Indicative Settlement";
        case Issue::IndicativeSettlement: return "Indicative Settlement";
        case Issue::InitialSettlement: return "Initial Settlement";
        case Issue::ReissuedSettlement: return "Reissued Settlement";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Issue value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
