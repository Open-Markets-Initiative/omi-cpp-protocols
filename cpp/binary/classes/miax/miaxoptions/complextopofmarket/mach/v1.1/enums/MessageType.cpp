#include "MessageType.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SystemTimeMessage: return "System Time Message";
        case MessageType::SeriesUpdate: return "Series Update";
        case MessageType::ComplexStrategyDefinitionMessage: return "Complex Strategy Definition Message";
        case MessageType::SystemStateMessage: return "System State Message";
        case MessageType::CompactComplexTopOfMarketBidMessage: return "Compact Complex Top Of Market Bid Message";
        case MessageType::CompactComplexTopOfMarketOfferMessage: return "Compact Complex Top Of Market Offer Message";
        case MessageType::WideComplexTopOfMarketBidMessage: return "Wide Complex Top Of Market Bid Message";
        case MessageType::WideComplexTopOfMarketOfferMessage: return "Wide Complex Top Of Market Offer Message";
        case MessageType::CompactComplexDoubleSidedTopOfMarketMessage: return "Compact Complex Double Sided Top Of Market Message";
        case MessageType::WideComplexDoubleSidedTopOfMarketMessage: return "Wide Complex Double Sided Top Of Market Message";
        case MessageType::StrategyTradeMessage: return "Strategy Trade Message";
        case MessageType::UnderlyingTradingStatusMessage: return "Underlying Trading Status Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
