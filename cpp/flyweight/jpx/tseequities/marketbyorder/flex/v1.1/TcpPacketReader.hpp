#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/TcpPacket.hpp"
#include "enums/PacketType.hpp"
#include "messages/LoginRequestRetransmissionMessage.hpp"
#include "messages/LoginRequestSnapshotMessage.hpp"
#include "messages/LoginResultAcceptedMessage.hpp"
#include "messages/LoginResultRejectedMessage.hpp"
#include "messages/MessageResponseMessage.hpp"
#include "messages/EndOfMessageMessage.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Reads a Tcp Packet in place: its headers, then each message its frames carry, handed to the
// handler as a view of its bytes. A handler declares an on() for each view it wants; a view it
// declares none for is passed over, and a code no message answers to goes to on_unknown(code,
// body) when it declares one.
struct TcpPacketReader {
    // Read one packet; what it returns is how many of the bytes the packet took.
    template <typename Handler>
    static std::size_t read(std::span<const std::byte> bytes, Handler& handler) {
        wire::require(TcpPacket::name, TcpPacket::minimum_size, bytes.size());
        const TcpPacket packet{ bytes };
        if constexpr (requires { handler.on(packet); }) { handler.on(packet); }

        const std::size_t offset = packet.encoded_size();
        const std::size_t packet_size = wire::count(packet.tcp_packet_header().packet_length()) + 2;
        wire::require(TcpPacket::name, packet_size, bytes.size());
        return offset + dispatch(packet, bytes.subspan(offset, packet_size - offset), handler);
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const TcpPacket& packet, std::span<const std::byte> body, Handler& handler) {
        switch (packet.tcp_packet_header().packet_type()) {
            case PacketType::LoginRequestRetransmissionMessage: return handle<LoginRequestRetransmissionMessage>(body, handler);
            case PacketType::LoginRequestSnapshotMessage: return handle<LoginRequestSnapshotMessage>(body, handler);
            case PacketType::LoginResultAcceptedMessage: return handle<LoginResultAcceptedMessage>(body, handler);
            case PacketType::LoginResultRejectedMessage: return handle<LoginResultRejectedMessage>(body, handler);
            case PacketType::MessageResponseMessage: return handle<MessageResponseMessage>(body, handler);
            case PacketType::EndOfMessageMessage: return handle<EndOfMessageMessage>(body, handler);
            default:
                if constexpr (requires { handler.on_unknown(packet.tcp_packet_header().packet_type(), body); }) { handler.on_unknown(packet.tcp_packet_header().packet_type(), body); }
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

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
