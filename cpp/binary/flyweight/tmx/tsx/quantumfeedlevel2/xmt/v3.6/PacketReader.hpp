// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: PacketReader.hpp
#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"
#include "structs/HeartbeatBody.hpp"
#include "enums/MsgType.hpp"
#include "messages/SymbolStatusMessage.hpp"
#include "messages/OrderBookMessage.hpp"
#include "messages/OrderBookTermsMessage.hpp"
#include "messages/AssignCopOrdersMessage.hpp"
#include "messages/AssignCopNoOrdersMessage.hpp"
#include "messages/AssignLimitMessage.hpp"
#include "messages/MarketStateUpdateMessage.hpp"
#include "messages/MocImbalanceMessage.hpp"
#include "messages/OrderBookedMessage.hpp"
#include "messages/OrderBookedTermsMessage.hpp"
#include "messages/OrderCancelledMessage.hpp"
#include "messages/OrderCancelledTermsMessage.hpp"
#include "messages/OrderPriceTimeAssignedMessage.hpp"
#include "messages/OrderPriceTimeAssignedTermsMessage.hpp"
#include "messages/StockStatusMessage.hpp"
#include "messages/TradeReportMessage.hpp"
#include "messages/TradeReportTermsMessage.hpp"
#include "messages/TradeCancelledMessage.hpp"
#include "messages/TradeCancelledTermsMessage.hpp"
#include "messages/TradeCorrectionMessage.hpp"
#include "messages/TradeCorrectionTermsMessage.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

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

        // the packet holds nothing after its headers
        if (!(packet.frame_header().message_length() > 6)) { return packet.encoded_size(); }

        // Heartbeat Body: the packet carries it in place of frames
        if (const HeartbeatBody heartbeat_body{ bytes.subspan(packet.encoded_size()), packet.frame_header().num_body() }; bytes.size() - packet.encoded_size() >= 3 && (static_cast<char>(heartbeat_body.body_header().msg_type()) == '0')) {
            wire::require(HeartbeatBody::name, HeartbeatBody::minimum_size, heartbeat_body.bytes().size());
            const std::size_t heartbeat_body_size = wire::count(heartbeat_body.body_header().msg_length());
            wire::require(HeartbeatBody::name, packet.encoded_size() + heartbeat_body_size, bytes.size());
            const HeartbeatBody bounded{ bytes.subspan(packet.encoded_size(), heartbeat_body_size), packet.frame_header().num_body() };
            if constexpr (requires { handler.on(bounded); }) { handler.on(bounded); }
            return packet.encoded_size() + heartbeat_body_size;
        }

        std::size_t offset = packet.encoded_size();
        const std::size_t count = wire::count(packet.frame_header().num_body());

        for (std::size_t index = 0; index < count; ++index) {
            const std::size_t start = offset;
            wire::require(Frame::name, offset + Frame::minimum_size, bytes.size());
            const Frame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            const std::size_t frame_size = wire::count(frame.body_header().msg_length());
            wire::require(Packet::name, start + frame_size, bytes.size());
            dispatch(frame, bytes.subspan(offset, start + frame_size - offset), handler);
            offset = start + frame_size;
        }

        return offset;
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const Frame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.body_header().msg_type()) {
            case MsgType::SymbolStatusMessage: return handle<SymbolStatusMessage>(body, handler);
            case MsgType::OrderBookMessage: return handle<OrderBookMessage>(body, handler);
            case MsgType::OrderBookTermsMessage: return handle<OrderBookTermsMessage>(body, handler);
            case MsgType::AssignCopOrdersMessage: return handle<AssignCopOrdersMessage>(body, handler);
            case MsgType::AssignCopNoOrdersMessage: return handle<AssignCopNoOrdersMessage>(body, handler);
            case MsgType::AssignLimitMessage: return handle<AssignLimitMessage>(body, handler);
            case MsgType::MarketStateUpdateMessage: return handle<MarketStateUpdateMessage>(body, handler);
            case MsgType::MocImbalanceMessage: return handle<MocImbalanceMessage>(body, handler);
            case MsgType::OrderBookedMessage: return handle<OrderBookedMessage>(body, handler);
            case MsgType::OrderBookedTermsMessage: return handle<OrderBookedTermsMessage>(body, handler);
            case MsgType::OrderCancelledMessage: return handle<OrderCancelledMessage>(body, handler);
            case MsgType::OrderCancelledTermsMessage: return handle<OrderCancelledTermsMessage>(body, handler);
            case MsgType::OrderPriceTimeAssignedMessage: return handle<OrderPriceTimeAssignedMessage>(body, handler);
            case MsgType::OrderPriceTimeAssignedTermsMessage: return handle<OrderPriceTimeAssignedTermsMessage>(body, handler);
            case MsgType::StockStatusMessage: return handle<StockStatusMessage>(body, handler);
            case MsgType::TradeReportMessage: return handle<TradeReportMessage>(body, handler);
            case MsgType::TradeReportTermsMessage: return handle<TradeReportTermsMessage>(body, handler);
            case MsgType::TradeCancelledMessage: return handle<TradeCancelledMessage>(body, handler);
            case MsgType::TradeCancelledTermsMessage: return handle<TradeCancelledTermsMessage>(body, handler);
            case MsgType::TradeCorrectionMessage: return handle<TradeCorrectionMessage>(body, handler);
            case MsgType::TradeCorrectionTermsMessage: return handle<TradeCorrectionTermsMessage>(body, handler);
            default:
                if constexpr (requires { handler.on_unknown(frame.body_header().msg_type(), body); }) { handler.on_unknown(frame.body_header().msg_type(), body); }
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

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
