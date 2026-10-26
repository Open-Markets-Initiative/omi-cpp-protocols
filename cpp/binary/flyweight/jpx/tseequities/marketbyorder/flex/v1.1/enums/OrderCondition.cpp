#include "OrderCondition.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

std::string_view to_string(OrderCondition value) {
    switch (value) {
        case OrderCondition::Nonconditional: return "Nonconditional";
        case OrderCondition::Onopen: return "Onopen";
        case OrderCondition::Onclose: return "Onclose";
        case OrderCondition::Funari: return "Funari";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OrderCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
