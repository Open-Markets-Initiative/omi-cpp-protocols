#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"
#include "enums/MessageType.hpp"
#include "messages/SequenceNumberResetMessage.hpp"
#include "messages/SourceTimeReferenceMessage.hpp"
#include "messages/SymbolIndexMappingMessage.hpp"
#include "messages/RetransmissionRequestMessage.hpp"
#include "messages/RequestResponseMessage.hpp"
#include "messages/HeartbeatResponseMessage.hpp"
#include "messages/SymbolIndexMappingRequestMessage.hpp"
#include "messages/RefreshRequestMessage.hpp"
#include "messages/MessageUnavailableMessage.hpp"
#include "messages/SymbolClearMessage.hpp"
#include "messages/SecurityStatusMessage.hpp"
#include "messages/RefreshHeaderMessage.hpp"
#include "messages/QuoteMessage.hpp"

namespace nyse::nyseequities::bbo::pillar::v2_5_b {

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
        if (static_cast<std::uint8_t>(packet.packet_header().delivery_flag()) == 1) { return packet.encoded_size(); }

        std::size_t offset = packet.encoded_size();
        const std::size_t count = wire::count(packet.packet_header().number_msgs());

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
            case MessageType::SequenceNumberResetMessage: return handle<SequenceNumberResetMessage>(body, handler);
            case MessageType::SourceTimeReferenceMessage: return handle<SourceTimeReferenceMessage>(body, handler);
            case MessageType::SymbolIndexMappingMessage: return handle<SymbolIndexMappingMessage>(body, handler);
            case MessageType::RetransmissionRequestMessage: return handle<RetransmissionRequestMessage>(body, handler);
            case MessageType::RequestResponseMessage: return handle<RequestResponseMessage>(body, handler);
            case MessageType::HeartbeatResponseMessage: return handle<HeartbeatResponseMessage>(body, handler);
            case MessageType::SymbolIndexMappingRequestMessage: return handle<SymbolIndexMappingRequestMessage>(body, handler);
            case MessageType::RefreshRequestMessage: return handle<RefreshRequestMessage>(body, handler);
            case MessageType::MessageUnavailableMessage: return handle<MessageUnavailableMessage>(body, handler);
            case MessageType::SymbolClearMessage: return handle<SymbolClearMessage>(body, handler);
            case MessageType::SecurityStatusMessage: return handle<SecurityStatusMessage>(body, handler);
            case MessageType::RefreshHeaderMessage: return handle<RefreshHeaderMessage>(body, handler);
            case MessageType::QuoteMessage: return handle<QuoteMessage>(body, handler);
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

} // namespace nyse::nyseequities::bbo::pillar::v2_5_b
