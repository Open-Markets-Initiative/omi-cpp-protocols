#include "Side.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

std::string_view to_string(Side value) {
    switch (value) {
        case Side::BuyOrder: return "Buy Order";
        case Side::SellOrder: return "Sell Order";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Side value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace lseg::millennium::level2::mitch::v11_9
