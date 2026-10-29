#include "Factory.hpp"

#include "definitions.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case OutrightMarketDepthBuyMessage::message_type: return std::make_unique<OutrightMarketDepthBuyMessage>();
        case OutrightMarketDepthSellMessage::message_type: return std::make_unique<OutrightMarketDepthSellMessage>();
        case UnderlyingStatusMessage::message_type: return std::make_unique<UnderlyingStatusMessage>();
        case OutrightSeriesStatusMessage::message_type: return std::make_unique<OutrightSeriesStatusMessage>();
        case RefreshOutrightMarketDepthBuyMessage::message_type: return std::make_unique<RefreshOutrightMarketDepthBuyMessage>();
        case RefreshOutrightMarketDepthSellMessage::message_type: return std::make_unique<RefreshOutrightMarketDepthSellMessage>();
        case UnderlyingIndexMappingMessage::message_type: return std::make_unique<UnderlyingIndexMappingMessage>();
        case SeriesIndexMappingMessage::message_type: return std::make_unique<SeriesIndexMappingMessage>();
        case StreamIdMessage::message_type: return std::make_unique<StreamIdMessage>();
        case SequenceNumberResetMessage::message_type: return std::make_unique<SequenceNumberResetMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
