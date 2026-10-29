#include "SideIndicator.hpp"

namespace cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29 {

std::string_view to_string(SideIndicator value) {
    switch (value) {
        case SideIndicator::BuyOrder: return "Buy Order";
        case SideIndicator::SellOrder: return "Sell Order";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SideIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29
