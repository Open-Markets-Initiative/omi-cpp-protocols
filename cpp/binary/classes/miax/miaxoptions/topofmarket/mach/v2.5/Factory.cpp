#include "Factory.hpp"

#include "definitions.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case ApplicationMessage::message_type: return std::make_unique<ApplicationMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

std::unique_ptr<Data> DataFactory::create(DataCode code) {
    switch (code) {
        case SystemTimeMessage::message_type: return std::make_unique<SystemTimeMessage>();
        case SimpleSeriesUpdateMessage::message_type: return std::make_unique<SimpleSeriesUpdateMessage>();
        case SystemStateMessage::message_type: return std::make_unique<SystemStateMessage>();
        case SimpleTopOfMarketBestBidOrOfferCompactBidMessage::message_type: return std::make_unique<SimpleTopOfMarketBestBidOrOfferCompactBidMessage>();
        case SimpleTopOfMarketBestBidOrOfferCompactOfferMessage::message_type: return std::make_unique<SimpleTopOfMarketBestBidOrOfferCompactOfferMessage>();
        case SimpleTopOfMarketBestBidOrOfferWideBidMessage::message_type: return std::make_unique<SimpleTopOfMarketBestBidOrOfferWideBidMessage>();
        case SimpleTopOfMarketBestBidOrOfferWideOfferMessage::message_type: return std::make_unique<SimpleTopOfMarketBestBidOrOfferWideOfferMessage>();
        case SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::message_type: return std::make_unique<SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage>();
        case SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::message_type: return std::make_unique<SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage>();
        case LastSaleMessage::message_type: return std::make_unique<LastSaleMessage>();
        case TradeCancelMessage::message_type: return std::make_unique<TradeCancelMessage>();
        case UnderlyingTradingStatusNotificationMessage::message_type: return std::make_unique<UnderlyingTradingStatusNotificationMessage>();
        default: return std::make_unique<UnknownData>(code);
    }
}

std::unique_ptr<TcpMessage> TcpMessageFactory::create(TcpMessageCode code) {
    switch (code) {
        case SequencedDataPacket::message_type: return std::make_unique<SequencedDataPacket>();
        case UnsequencedDataPacket::message_type: return std::make_unique<UnsequencedDataPacket>();
        case LoginRequest::message_type: return std::make_unique<LoginRequest>();
        case LoginResponse::message_type: return std::make_unique<LoginResponse>();
        case SynchronizationComplete::message_type: return std::make_unique<SynchronizationComplete>();
        case RetransmissionRequest::message_type: return std::make_unique<RetransmissionRequest>();
        case LogoutRequest::message_type: return std::make_unique<LogoutRequest>();
        case GoodbyePacket::message_type: return std::make_unique<GoodbyePacket>();
        case TestPacket::message_type: return std::make_unique<TestPacket>();
        default: return std::make_unique<UnknownTcpMessage>(code);
    }
}

std::unique_ptr<UnsequencedMessage> UnsequencedMessageFactory::create(UnsequencedMessageCode code) {
    switch (code) {
        case RefreshRequestMessage::message_type: return std::make_unique<RefreshRequestMessage>();
        case RefreshResponseMessage::message_type: return std::make_unique<RefreshResponseMessage>();
        case EndOfRefreshNotificationMessage::message_type: return std::make_unique<EndOfRefreshNotificationMessage>();
        default: return std::make_unique<UnknownUnsequencedMessage>(code);
    }
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
