#include "OrderUpdateAction.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

std::string_view to_string(OrderUpdateAction value) {
    switch (value) {
        case OrderUpdateAction::New: return "New";
        case OrderUpdateAction::Update: return "Update";
        case OrderUpdateAction::Delete: return "Delete";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OrderUpdateAction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_8
