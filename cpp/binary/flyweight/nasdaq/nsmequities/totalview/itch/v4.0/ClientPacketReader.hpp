#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/ClientPacket.hpp"
#include "structs/Frame.hpp"
#include "enums/ClientPacketType.hpp"
#include "messages/DebugPacket.hpp"
#include "messages/LoginRequestPacket.hpp"
#include "messages/UnsequencedDataPacket.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// Reads a Client Packet in place: its headers, then each message its frames carry, handed to
// the handler as a view of its bytes. A handler declares an on() for each view it wants; a
// view it declares none for is passed over, and a code no message answers to goes to
// on_unknown(code, body) when it declares one.
struct ClientPacketReader {
    // Read one packet; what it returns is how many of the bytes the packet took.
    template <typename Handler>
    static std::size_t read(std::span<const std::byte> bytes, Handler& handler) {
        wire::require(ClientPacket::name, ClientPacket::minimum_size, bytes.size());
        const ClientPacket packet{ bytes };
        if constexpr (requires { handler.on(packet); }) { handler.on(packet); }

        std::size_t offset = packet.encoded_size();

        while (offset < bytes.size()) {
            const std::size_t start = offset;

            // A frame the bytes do not hold in full is the caller's tail, not a fault: stop short of
            // it and leave it out of what this read took.
            if (bytes.size() - offset < Frame::minimum_size) { break; }

            const Frame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            const std::size_t frame_size = wire::count(frame.client_packet_header().packet_length()) + 2;
            if (frame_size < Frame::minimum_size) { throw DecodeError(ClientPacket::name, Frame::minimum_size, frame_size); }
            if (start + frame_size > bytes.size()) { offset = start; break; }
            dispatch(frame, bytes.subspan(offset, start + frame_size - offset), handler);
            offset = start + frame_size;
        }

        return offset;
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const Frame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.client_packet_header().client_packet_type()) {
            case ClientPacketType::DebugPacket: return handle<DebugPacket>(body, handler);
            case ClientPacketType::LoginRequestPacket: return handle<LoginRequestPacket>(body, handler);
            case ClientPacketType::UnsequencedDataPacket: return handle<UnsequencedDataPacket>(body, handler);
            default:
                if constexpr (requires { handler.on_unknown(frame.client_packet_header().client_packet_type(), body); }) { handler.on_unknown(frame.client_packet_header().client_packet_type(), body); }
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

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
