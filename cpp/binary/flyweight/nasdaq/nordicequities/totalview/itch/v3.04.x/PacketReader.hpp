#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"
#include "enums/MessageType.hpp"
#include "messages/SystemEventMessage.hpp"
#include "messages/OrderBookTradingActionMessage.hpp"
#include "messages/OrderBookDirectoryMessage.hpp"
#include "messages/AddOrderMessage.hpp"
#include "messages/AddOrderMpidAttributionMessage.hpp"
#include "messages/OrderExecutedMessage.hpp"
#include "messages/OrderExecutedWithPriceMessage.hpp"
#include "messages/OrderCancelMessage.hpp"
#include "messages/OrderDeleteMessage.hpp"
#include "messages/OrderBookFlushMessage.hpp"
#include "messages/OrderReplaceMessage.hpp"
#include "messages/TradeMessage.hpp"
#include "messages/CrossTradeMessage.hpp"
#include "messages/BrokenTradeMessage.hpp"
#include "messages/NoiiMessage.hpp"
#include "messages/MoiiMessage.hpp"
#include "messages/ExecutionSummaryMessage.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

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

        // End Of Session: the packet carries no messages
        if (packet.packet_header().message_count() == 65535) { return packet.encoded_size(); }

        std::size_t offset = packet.encoded_size();
        const std::size_t count = wire::count(packet.packet_header().message_count());

        for (std::size_t index = 0; index < count; ++index) {
            const std::size_t start = offset;
            wire::require(Frame::name, offset + Frame::minimum_size, bytes.size());
            const Frame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            const std::size_t frame_size = wire::count(frame.message_header().message_length()) + 2;
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
            case MessageType::SystemEventMessage: return handle<SystemEventMessage>(body, handler);
            case MessageType::OrderBookTradingActionMessage: return handle<OrderBookTradingActionMessage>(body, handler);
            case MessageType::OrderBookDirectoryMessage: return handle<OrderBookDirectoryMessage>(body, handler);
            case MessageType::AddOrderMessage: return handle<AddOrderMessage>(body, handler);
            case MessageType::AddOrderMpidAttributionMessage: return handle<AddOrderMpidAttributionMessage>(body, handler);
            case MessageType::OrderExecutedMessage: return handle<OrderExecutedMessage>(body, handler);
            case MessageType::OrderExecutedWithPriceMessage: return handle<OrderExecutedWithPriceMessage>(body, handler);
            case MessageType::OrderCancelMessage: return handle<OrderCancelMessage>(body, handler);
            case MessageType::OrderDeleteMessage: return handle<OrderDeleteMessage>(body, handler);
            case MessageType::OrderBookFlushMessage: return handle<OrderBookFlushMessage>(body, handler);
            case MessageType::OrderReplaceMessage: return handle<OrderReplaceMessage>(body, handler);
            case MessageType::TradeMessage: return handle<TradeMessage>(body, handler);
            case MessageType::CrossTradeMessage: return handle<CrossTradeMessage>(body, handler);
            case MessageType::BrokenTradeMessage: return handle<BrokenTradeMessage>(body, handler);
            case MessageType::NoiiMessage: return handle<NoiiMessage>(body, handler);
            case MessageType::MoiiMessage: return handle<MoiiMessage>(body, handler);
            case MessageType::ExecutionSummaryMessage: return handle<ExecutionSummaryMessage>(body, handler);
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

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
