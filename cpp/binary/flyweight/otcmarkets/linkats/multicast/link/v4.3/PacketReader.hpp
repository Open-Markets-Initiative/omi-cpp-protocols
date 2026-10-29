#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"
#include "enums/MessageType.hpp"
#include "messages/StartOfSpinMessage.hpp"
#include "messages/EndOfSpinMessage.hpp"
#include "messages/MarketOpenMessage.hpp"
#include "messages/MarketCloseMessage.hpp"
#include "messages/SecurityMessage.hpp"
#include "messages/QuoteMessage.hpp"
#include "messages/QuoteUpdateMessage.hpp"
#include "messages/InsideMessage.hpp"
#include "messages/InsideUpdateMessage.hpp"
#include "messages/ReferencePriceMessage.hpp"
#include "messages/ReferencePriceUpdateMessage.hpp"
#include "messages/ExtendedSecurityMessage.hpp"
#include "messages/ExtendedSecurityNoCusipMessage.hpp"
#include "messages/TradeMessage.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

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

        // Heartbeat Packet: the packet carries no messages
        if (packet.packet_header().packet_flag().heartbeat() == 1) { return packet.encoded_size(); }

        std::size_t offset = packet.encoded_size();
        const std::size_t count = wire::count(packet.packet_header().message_count());

        for (std::size_t index = 0; index < count; ++index) {
            const std::size_t start = offset;
            wire::require(Frame::name, offset + Frame::minimum_size, bytes.size());
            const Frame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            const std::size_t frame_size = wire::count(frame.message_header().message_size());
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
            case MessageType::StartOfSpinMessage: return handle<StartOfSpinMessage>(body, handler);
            case MessageType::EndOfSpinMessage: return handle<EndOfSpinMessage>(body, handler);
            case MessageType::MarketOpenMessage: return handle<MarketOpenMessage>(body, handler);
            case MessageType::MarketCloseMessage: return handle<MarketCloseMessage>(body, handler);
            case MessageType::SecurityMessage: return handle<SecurityMessage>(body, handler);
            case MessageType::QuoteMessage: return handle<QuoteMessage>(body, handler);
            case MessageType::QuoteUpdateMessage: return handle<QuoteUpdateMessage>(body, handler);
            case MessageType::InsideMessage: return handle<InsideMessage>(body, handler);
            case MessageType::InsideUpdateMessage: return handle<InsideUpdateMessage>(body, handler);
            case MessageType::ReferencePriceMessage: return handle<ReferencePriceMessage>(body, handler);
            case MessageType::ReferencePriceUpdateMessage: return handle<ReferencePriceUpdateMessage>(body, handler);
            case MessageType::ExtendedSecurityMessage: return handle<ExtendedSecurityMessage>(body, handler);
            case MessageType::ExtendedSecurityNoCusipMessage: return handle<ExtendedSecurityNoCusipMessage>(body, handler);
            case MessageType::TradeMessage: return handle<TradeMessage>(body, handler);
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

} // namespace otcmarkets::linkats::multicast::link::v4_3
