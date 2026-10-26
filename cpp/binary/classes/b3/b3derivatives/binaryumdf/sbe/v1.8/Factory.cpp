#include "Factory.hpp"

#include "definitions.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SequenceMessage::message_type: return std::make_unique<SequenceMessage>();
        case EmptyBookMessage::message_type: return std::make_unique<EmptyBookMessage>();
        case ChannelReset11Message::message_type: return std::make_unique<ChannelReset11Message>();
        case SecurityStatus3Message::message_type: return std::make_unique<SecurityStatus3Message>();
        case SecurityGroupPhase10Message::message_type: return std::make_unique<SecurityGroupPhase10Message>();
        case DeprecatedSecurityDefinitionMessage::message_type: return std::make_unique<DeprecatedSecurityDefinitionMessage>();
        case SecurityDefinitionMessage::message_type: return std::make_unique<SecurityDefinitionMessage>();
        case News5Message::message_type: return std::make_unique<News5Message>();
        case OpeningPrice15Message::message_type: return std::make_unique<OpeningPrice15Message>();
        case TheoreticalOpeningPrice16Message::message_type: return std::make_unique<TheoreticalOpeningPrice16Message>();
        case ClosingPrice17Message::message_type: return std::make_unique<ClosingPrice17Message>();
        case AuctionImbalance19Message::message_type: return std::make_unique<AuctionImbalance19Message>();
        case PriceBand20Message::message_type: return std::make_unique<PriceBand20Message>();
        case QuantityBand21Message::message_type: return std::make_unique<QuantityBand21Message>();
        case PriceBand22Message::message_type: return std::make_unique<PriceBand22Message>();
        case HighPrice24Message::message_type: return std::make_unique<HighPrice24Message>();
        case LowPrice25Message::message_type: return std::make_unique<LowPrice25Message>();
        case LastTradePrice27Message::message_type: return std::make_unique<LastTradePrice27Message>();
        case SettlementPrice28Message::message_type: return std::make_unique<SettlementPrice28Message>();
        case OpenInterest29Message::message_type: return std::make_unique<OpenInterest29Message>();
        case SnapshotFullRefreshHeader30Message::message_type: return std::make_unique<SnapshotFullRefreshHeader30Message>();
        case OrderMbO50Message::message_type: return std::make_unique<OrderMbO50Message>();
        case DeleteOrderMbO51Message::message_type: return std::make_unique<DeleteOrderMbO51Message>();
        case MassDeleteOrdersMbO52Message::message_type: return std::make_unique<MassDeleteOrdersMbO52Message>();
        case Trade53Message::message_type: return std::make_unique<Trade53Message>();
        case ForwardTrade54Message::message_type: return std::make_unique<ForwardTrade54Message>();
        case ExecutionSummary55Message::message_type: return std::make_unique<ExecutionSummary55Message>();
        case ExecutionStatistics56Message::message_type: return std::make_unique<ExecutionStatistics56Message>();
        case TradeBust57Message::message_type: return std::make_unique<TradeBust57Message>();
        case SnapshotFullRefreshOrdersMbO71Message::message_type: return std::make_unique<SnapshotFullRefreshOrdersMbO71Message>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
