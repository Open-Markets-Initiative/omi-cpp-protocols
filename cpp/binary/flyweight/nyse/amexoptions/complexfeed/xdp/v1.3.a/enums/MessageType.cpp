#include "MessageType.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::ComplexQuoteMessage: return "Complex Quote Message";
        case MessageType::ComplexTradeMessage: return "Complex Trade Message";
        case MessageType::ComplexCrossingRfqMessage: return "Complex Crossing Rfq Message";
        case MessageType::ComplexCubeRfqMessage: return "Complex Cube Rfq Message";
        case MessageType::ComplexStatusMessage: return "Complex Status Message";
        case MessageType::RefreshComplexQuoteMessage: return "Refresh Complex Quote Message";
        case MessageType::RefreshComplexTradeMessage: return "Refresh Complex Trade Message";
        case MessageType::ComplexSymbolDefinitionMessage: return "Complex Symbol Definition Message";
        case MessageType::StreamIdMessage: return "Stream Id Message";
        case MessageType::SequenceNumberResetMessage: return "Sequence Number Reset Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
