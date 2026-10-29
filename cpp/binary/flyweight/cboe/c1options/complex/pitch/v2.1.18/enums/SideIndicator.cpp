#include "SideIndicator.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

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

} // namespace cboe::c1options::complex::pitch::v2_1_18
