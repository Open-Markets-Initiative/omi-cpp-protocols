#include "Event.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

std::string_view to_string(Event value) {
    switch (value) {
        case Event::StartOfSession: return "Start Of Session";
        case Event::MarketAcceptingOrders: return "Market Accepting Orders";
        case Event::MarketOpenForTrading: return "Market Open For Trading";
        case Event::MarketClosedForTrading: return "Market Closed For Trading";
        case Event::EndOfSession: return "End Of Session";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Event value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
