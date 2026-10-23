#include "Side.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

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

} // namespace lseg::lse::level2mbo::gtp::v26_2
