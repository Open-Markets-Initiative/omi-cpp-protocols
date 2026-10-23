#include "Side.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

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

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
