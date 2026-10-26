#include "TriggeredSide.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

std::string_view to_string(TriggeredSide value) {
    switch (value) {
        case TriggeredSide::SellOrder: return "Sell Order";
        case TriggeredSide::BuyOrder: return "Buy Order";
        case TriggeredSide::ItayoseExecution: return "Itayose Execution";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TriggeredSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
