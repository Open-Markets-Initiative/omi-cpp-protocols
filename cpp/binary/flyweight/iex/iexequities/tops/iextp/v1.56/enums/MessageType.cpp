#include "MessageType.hpp"

namespace iex::iexequities::tops::iextp::v1_56 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::QuoteUpdateMessage: return "Quote Update Message";
        case MessageType::TradeReportMessage: return "Trade Report Message";
        case MessageType::TradeBreakMessage: return "Trade Break Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace iex::iexequities::tops::iextp::v1_56
