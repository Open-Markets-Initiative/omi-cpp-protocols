#include "OrderType.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

std::string_view to_string(OrderType value) {
    switch (value) {
        case OrderType::DlpOrder: return "Dlp Order";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OrderType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jnx::jnxequities::pts::itch::v1_6
