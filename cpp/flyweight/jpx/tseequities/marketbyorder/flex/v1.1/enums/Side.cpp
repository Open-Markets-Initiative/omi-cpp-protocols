#include "Side.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

std::string_view to_string(Side value) {
    switch (value) {
        case Side::SellOrder: return "Sell Order";
        case Side::BuyOrder: return "Buy Order";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Side value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
