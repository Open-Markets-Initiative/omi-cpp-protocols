#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/Packet.hpp"
#include "structs/PacketFrame.hpp"
#include "enums/MessageType.hpp"
#include "messages/PayloadTimestampMessage.hpp"
#include "messages/PayloadSystemEventMessage.hpp"
#include "messages/PayloadOptionsDirectoryMessage.hpp"
#include "messages/PayloadTradingActionMessage.hpp"
#include "messages/PayloadSecurityOpenClosedMessage.hpp"
#include "messages/PayloadShortBestBidAndAskUpdateMessage.hpp"
#include "messages/PayloadLongBestBidAndAskUpdateMessage.hpp"
#include "messages/PayloadShortBestAskUpdateMessage.hpp"
#include "messages/PayloadShortBestBidUpdateMessage.hpp"
#include "messages/PayloadLongBestAskUpdateMessage.hpp"
#include "messages/PayloadLongBestBidUpdateMessage.hpp"
#include "messages/PayloadTradeReportMessage.hpp"
#include "messages/PayloadBrokenTradeReportMessage.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

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
            wire::require(PacketFrame::name, offset + PacketFrame::minimum_size, bytes.size());
            const PacketFrame frame{ bytes.subspan(offset) };
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
    static std::size_t dispatch(const PacketFrame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.message_header().message_type()) {
            case MessageType::TimestampMessage: return handle<PayloadTimestampMessage>(body, handler);
            case MessageType::SystemEventMessage: return handle<PayloadSystemEventMessage>(body, handler);
            case MessageType::OptionsDirectoryMessage: return handle<PayloadOptionsDirectoryMessage>(body, handler);
            case MessageType::TradingActionMessage: return handle<PayloadTradingActionMessage>(body, handler);
            case MessageType::SecurityOpenClosedMessage: return handle<PayloadSecurityOpenClosedMessage>(body, handler);
            case MessageType::ShortBestBidAndAskUpdateMessage: return handle<PayloadShortBestBidAndAskUpdateMessage>(body, handler);
            case MessageType::LongBestBidAndAskUpdateMessage: return handle<PayloadLongBestBidAndAskUpdateMessage>(body, handler);
            case MessageType::ShortBestAskUpdateMessage: return handle<PayloadShortBestAskUpdateMessage>(body, handler);
            case MessageType::ShortBestBidUpdateMessage: return handle<PayloadShortBestBidUpdateMessage>(body, handler);
            case MessageType::LongBestAskUpdateMessage: return handle<PayloadLongBestAskUpdateMessage>(body, handler);
            case MessageType::LongBestBidUpdateMessage: return handle<PayloadLongBestBidUpdateMessage>(body, handler);
            case MessageType::TradeReportMessage: return handle<PayloadTradeReportMessage>(body, handler);
            case MessageType::BrokenTradeReportMessage: return handle<PayloadBrokenTradeReportMessage>(body, handler);
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

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
