#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"
#include "enums/MessageType.hpp"
#include "messages/TimeMessage.hpp"
#include "messages/UnitClearMessage.hpp"
#include "messages/AddOrderLongMessage.hpp"
#include "messages/AddOrderShortMessage.hpp"
#include "messages/AddOrderExpandedMessage.hpp"
#include "messages/OrderExecutedMessage.hpp"
#include "messages/OrderExecutedAtPriceSizeMessage.hpp"
#include "messages/ReduceSizeLongMessage.hpp"
#include "messages/ReduceSizeShortMessage.hpp"
#include "messages/ModifyOrderLongMessage.hpp"
#include "messages/ModifyOrderShortMessage.hpp"
#include "messages/DeleteOrderMessage.hpp"
#include "messages/TradeLongMessage.hpp"
#include "messages/TradeShortMessage.hpp"
#include "messages/TradeExpandedMessage.hpp"
#include "messages/TradeBreakMessage.hpp"
#include "messages/EndOfSessionMessage.hpp"
#include "messages/SymbolMappingMessage.hpp"
#include "messages/TradingStatusMessage.hpp"
#include "messages/AuctionUpdateMessage.hpp"
#include "messages/AuctionSummaryMessage.hpp"
#include "messages/AuctionNotificationMessage.hpp"
#include "messages/AuctionCancelMessage.hpp"
#include "messages/AuctionTradeMessage.hpp"
#include "messages/RetailPriceImprovementMessage.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// Reads a Packet in place: its headers, then each message its frames carry, handed to the
// handler as a view of its bytes. A handler declares an on() for each view it wants; a view it
// declares none for is passed over, and a code no message answers to goes to on_unknown(code,
// body) when it declares one.
struct PacketReader {
    // Read one packet; what it returns is how many of the bytes the packet took.
    template <typename Handler>
    static std::size_t read(std::span<const std::byte> bytes, Handler& handler) {
        wire::require(Packet::name, Packet::minimum_size, bytes.size());
        const Packet packet{ bytes };
        if constexpr (requires { handler.on(packet); }) { handler.on(packet); }

        // Heartbeat: the packet carries no messages
        if (packet.packet_header().message_count() == 0) { return packet.encoded_size(); }

        std::size_t offset = packet.encoded_size();
        const std::size_t count = wire::count(packet.packet_header().message_count());

        for (std::size_t index = 0; index < count; ++index) {
            const std::size_t start = offset;
            wire::require(Frame::name, offset + Frame::minimum_size, bytes.size());
            const Frame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            const std::size_t frame_size = wire::count(frame.message_header().message_length());
            wire::require(Packet::name, start + frame_size, bytes.size());
            dispatch(frame, bytes.subspan(offset, start + frame_size - offset), handler);
            offset = start + frame_size;
        }

        return offset;
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const Frame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.message_header().message_type()) {
            case MessageType::TimeMessage: return handle<TimeMessage>(body, handler);
            case MessageType::UnitClearMessage: return handle<UnitClearMessage>(body, handler);
            case MessageType::AddOrderLongMessage: return handle<AddOrderLongMessage>(body, handler);
            case MessageType::AddOrderShortMessage: return handle<AddOrderShortMessage>(body, handler);
            case MessageType::AddOrderExpandedMessage: return handle<AddOrderExpandedMessage>(body, handler);
            case MessageType::OrderExecutedMessage: return handle<OrderExecutedMessage>(body, handler);
            case MessageType::OrderExecutedAtPriceSizeMessage: return handle<OrderExecutedAtPriceSizeMessage>(body, handler);
            case MessageType::ReduceSizeLongMessage: return handle<ReduceSizeLongMessage>(body, handler);
            case MessageType::ReduceSizeShortMessage: return handle<ReduceSizeShortMessage>(body, handler);
            case MessageType::ModifyOrderLongMessage: return handle<ModifyOrderLongMessage>(body, handler);
            case MessageType::ModifyOrderShortMessage: return handle<ModifyOrderShortMessage>(body, handler);
            case MessageType::DeleteOrderMessage: return handle<DeleteOrderMessage>(body, handler);
            case MessageType::TradeLongMessage: return handle<TradeLongMessage>(body, handler);
            case MessageType::TradeShortMessage: return handle<TradeShortMessage>(body, handler);
            case MessageType::TradeExpandedMessage: return handle<TradeExpandedMessage>(body, handler);
            case MessageType::TradeBreakMessage: return handle<TradeBreakMessage>(body, handler);
            case MessageType::EndOfSessionMessage: return handle<EndOfSessionMessage>(body, handler);
            case MessageType::SymbolMappingMessage: return handle<SymbolMappingMessage>(body, handler);
            case MessageType::TradingStatusMessage: return handle<TradingStatusMessage>(body, handler);
            case MessageType::AuctionUpdateMessage: return handle<AuctionUpdateMessage>(body, handler);
            case MessageType::AuctionSummaryMessage: return handle<AuctionSummaryMessage>(body, handler);
            case MessageType::AuctionNotificationMessage: return handle<AuctionNotificationMessage>(body, handler);
            case MessageType::AuctionCancelMessage: return handle<AuctionCancelMessage>(body, handler);
            case MessageType::AuctionTradeMessage: return handle<AuctionTradeMessage>(body, handler);
            case MessageType::RetailPriceImprovementMessage: return handle<RetailPriceImprovementMessage>(body, handler);
            default:
                if constexpr (requires { handler.on_unknown(frame.message_header().message_type(), body); }) { handler.on_unknown(frame.message_header().message_type(), body); }
                return body.size();
        }
    }

    template <typename Message, typename Handler, typename... Handed>
    static std::size_t handle(std::span<const std::byte> body, Handler& handler, Handed... handed) {
        wire::require(Message::name, Message::minimum_size, body.size());
        const Message message{ body, handed... };
        if constexpr (requires { handler.on(message); }) { handler.on(message); }
        return message.encoded_size();
    }
};

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
