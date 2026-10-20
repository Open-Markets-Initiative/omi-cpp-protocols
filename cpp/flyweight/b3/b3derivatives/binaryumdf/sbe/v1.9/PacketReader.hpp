#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"
#include "enums/TemplateId.hpp"
#include "messages/SequenceMessage.hpp"
#include "messages/EmptyBookMessage.hpp"
#include "messages/ChannelReset11Message.hpp"
#include "messages/SecurityStatus3Message.hpp"
#include "messages/SecurityGroupPhase10Message.hpp"
#include "messages/SecurityDefinitionMessage.hpp"
#include "messages/News5Message.hpp"
#include "messages/OpeningPrice15Message.hpp"
#include "messages/TheoreticalOpeningPrice16Message.hpp"
#include "messages/ClosingPrice17Message.hpp"
#include "messages/AuctionImbalance19Message.hpp"
#include "messages/QuantityBand21Message.hpp"
#include "messages/PriceBand22Message.hpp"
#include "messages/HighPrice24Message.hpp"
#include "messages/LowPrice25Message.hpp"
#include "messages/LastTradePrice27Message.hpp"
#include "messages/SettlementPrice28Message.hpp"
#include "messages/OpenInterest29Message.hpp"
#include "messages/SnapshotFullRefreshHeader30Message.hpp"
#include "messages/OrderMbO50Message.hpp"
#include "messages/DeleteOrderMbO51Message.hpp"
#include "messages/MassDeleteOrdersMbO52Message.hpp"
#include "messages/Trade53Message.hpp"
#include "messages/ForwardTrade54Message.hpp"
#include "messages/ExecutionSummary55Message.hpp"
#include "messages/ExecutionStatistics56Message.hpp"
#include "messages/TradeBust57Message.hpp"
#include "messages/SnapshotFullRefreshOrdersMbO71Message.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// Reads a Packet in place: its headers, then each message its frames carry, handed to the
// handler as a view of its bytes. A handler declares an on() for each view it wants; a view it
// declares none for is passed over, and a code no message answers to goes to on_unknown() when
// it declares one.
struct PacketReader {
    // Read one packet; what it returns is how many of the bytes the packet took.
    template <typename Handler>
    static std::size_t read(std::span<const std::byte> bytes, Handler& handler) {
        wire::require(Packet::name, Packet::minimum_size, bytes.size());
        const Packet packet{ bytes };
        if constexpr (requires { handler.on(packet); }) { handler.on(packet); }

        std::size_t offset = packet.encoded_size();

        while (offset < bytes.size()) {
            const std::size_t start = offset;
            wire::require(Frame::name, offset + Frame::minimum_size, bytes.size());
            const Frame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            const std::size_t frame_size = static_cast<std::size_t>(frame.framing_header().message_length());
            wire::require(Packet::name, start + frame_size, bytes.size());
            dispatch(frame, bytes.subspan(offset, start + frame_size - offset), handler);
            offset = start + frame_size;
        }

        return offset;
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const Frame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.message_header().template_id()) {
            case TemplateId::Sequence2Message: return handle<SequenceMessage>(body, handler);
            case TemplateId::EmptyBook9Message: return handle<EmptyBookMessage>(body, handler);
            case TemplateId::ChannelReset11Message: return handle<ChannelReset11Message>(body, handler);
            case TemplateId::SecurityStatus3Message: return handle<SecurityStatus3Message>(body, handler);
            case TemplateId::SecurityGroupPhase10Message: return handle<SecurityGroupPhase10Message>(body, handler);
            case TemplateId::SecurityDefinitionMessage: return handle<SecurityDefinitionMessage>(body, handler);
            case TemplateId::News5Message: return handle<News5Message>(body, handler);
            case TemplateId::OpeningPrice15Message: return handle<OpeningPrice15Message>(body, handler);
            case TemplateId::TheoreticalOpeningPrice16Message: return handle<TheoreticalOpeningPrice16Message>(body, handler);
            case TemplateId::ClosingPrice17Message: return handle<ClosingPrice17Message>(body, handler);
            case TemplateId::AuctionImbalance19Message: return handle<AuctionImbalance19Message>(body, handler);
            case TemplateId::QuantityBand21Message: return handle<QuantityBand21Message>(body, handler);
            case TemplateId::PriceBand22Message: return handle<PriceBand22Message>(body, handler);
            case TemplateId::HighPrice24Message: return handle<HighPrice24Message>(body, handler);
            case TemplateId::LowPrice25Message: return handle<LowPrice25Message>(body, handler);
            case TemplateId::LastTradePrice27Message: return handle<LastTradePrice27Message>(body, handler);
            case TemplateId::SettlementPrice28Message: return handle<SettlementPrice28Message>(body, handler);
            case TemplateId::OpenInterest29Message: return handle<OpenInterest29Message>(body, handler);
            case TemplateId::SnapshotFullRefreshHeader30Message: return handle<SnapshotFullRefreshHeader30Message>(body, handler);
            case TemplateId::OrderMbO50Message: return handle<OrderMbO50Message>(body, handler);
            case TemplateId::DeleteOrderMbO51Message: return handle<DeleteOrderMbO51Message>(body, handler);
            case TemplateId::MassDeleteOrdersMbO52Message: return handle<MassDeleteOrdersMbO52Message>(body, handler);
            case TemplateId::Trade53Message: return handle<Trade53Message>(body, handler);
            case TemplateId::ForwardTrade54Message: return handle<ForwardTrade54Message>(body, handler);
            case TemplateId::ExecutionSummary55Message: return handle<ExecutionSummary55Message>(body, handler);
            case TemplateId::ExecutionStatistics56Message: return handle<ExecutionStatistics56Message>(body, handler);
            case TemplateId::TradeBust57Message: return handle<TradeBust57Message>(body, handler);
            case TemplateId::SnapshotFullRefreshOrdersMbO71Message: return handle<SnapshotFullRefreshOrdersMbO71Message>(body, handler);
            default:
                if constexpr (requires { handler.on_unknown(frame.message_header().template_id(), body); }) { handler.on_unknown(frame.message_header().template_id(), body); }
                return body.size();
        }
    }

    template <typename Message, typename Handler>
    static std::size_t handle(std::span<const std::byte> body, Handler& handler) {
        wire::require(Message::name, Message::minimum_size, body.size());
        const Message message{ body };
        if constexpr (requires { handler.on(message); }) { handler.on(message); }
        return message.encoded_size();
    }
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
