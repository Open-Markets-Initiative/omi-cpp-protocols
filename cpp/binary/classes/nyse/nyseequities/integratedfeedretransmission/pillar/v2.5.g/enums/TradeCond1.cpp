#include "TradeCond1.hpp"

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {

std::string_view to_string(TradeCond1 value) {
    switch (value) {
        case TradeCond1::RegularSale: return "Regular Sale";
        case TradeCond1::CashTexasOnly: return "Cash Texas Only";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeCond1 value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g
