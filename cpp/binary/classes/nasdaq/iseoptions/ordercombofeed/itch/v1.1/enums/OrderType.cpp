#include "OrderType.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

std::string_view to_string(OrderType value) {
    switch (value) {
        case OrderType::Market: return "Market";
        case OrderType::Limit: return "Limit";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OrderType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
