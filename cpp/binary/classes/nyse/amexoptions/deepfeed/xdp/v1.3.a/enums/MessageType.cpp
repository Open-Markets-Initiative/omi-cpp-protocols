#include "MessageType.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::OutrightMarketDepthBuyMessage: return "Outright Market Depth Buy Message";
        case MessageType::OutrightMarketDepthSellMessage: return "Outright Market Depth Sell Message";
        case MessageType::UnderlyingStatusMessage: return "Underlying Status Message";
        case MessageType::OutrightSeriesStatusMessage: return "Outright Series Status Message";
        case MessageType::RefreshOutrightMarketDepthBuyMessage: return "Refresh Outright Market Depth Buy Message";
        case MessageType::RefreshOutrightMarketDepthSellMessage: return "Refresh Outright Market Depth Sell Message";
        case MessageType::UnderlyingIndexMappingMessage: return "Underlying Index Mapping Message";
        case MessageType::SeriesIndexMappingMessage: return "Series Index Mapping Message";
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

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
