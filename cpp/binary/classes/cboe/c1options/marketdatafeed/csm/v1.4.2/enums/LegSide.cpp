#include "LegSide.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

std::string_view to_string(LegSide value) {
    switch (value) {
        case LegSide::BuyBid: return "Buy Bid";
        case LegSide::SellAsk: return "Sell Ask";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LegSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
