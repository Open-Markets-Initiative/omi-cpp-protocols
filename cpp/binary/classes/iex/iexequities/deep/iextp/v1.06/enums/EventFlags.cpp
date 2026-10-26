#include "EventFlags.hpp"

namespace iex::iexequities::deep::iextp::v1_06 {

std::string_view to_string(EventFlags value) {
    switch (value) {
        case EventFlags::OrderBookIsProcessingAnEvent: return "Order Book Is Processing An Event";
        case EventFlags::EventProcessingComplete: return "Event Processing Complete";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, EventFlags value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace iex::iexequities::deep::iextp::v1_06
