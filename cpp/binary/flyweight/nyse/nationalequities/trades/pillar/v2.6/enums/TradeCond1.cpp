#include "TradeCond1.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

std::string_view to_string(TradeCond1 value) {
    switch (value) {
        case TradeCond1::RegularSale: return "Regular Sale";
        case TradeCond1::Cash: return "Cash";
        case TradeCond1::RegularSaleTrfOnly: return "Regular Sale Trf Only";
        case TradeCond1::SellerTrfOnly: return "Seller Trf Only";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeCond1 value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nationalequities::trades::pillar::v2_6
