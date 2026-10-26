#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/ServerPacket.hpp"
#include "structs/ServerFrame.hpp"
#include "enums/ServerPacketType.hpp"
#include "messages/ServerPayloadDebugPacket.hpp"
#include "messages/LoginAcceptedPacket.hpp"
#include "messages/LoginRejectedPacket.hpp"
#include "messages/SequencedDataPacket.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Reads a Server Packet in place: its headers, then each message its frames carry, handed to
// the handler as a view of its bytes. A handler declares an on() for each view it wants; a
// view it declares none for is passed over, and a code no message answers to goes to
// on_unknown(code, body) when it declares one.
struct ServerPacketReader {
    // Read one packet; what it returns is how many of the bytes the packet took.
    template <typename Handler>
    static std::size_t read(std::span<const std::byte> bytes, Handler& handler) {
        wire::require(ServerPacket::name, ServerPacket::minimum_size, bytes.size());
        const ServerPacket packet{ bytes };
        if constexpr (requires { handler.on(packet); }) { handler.on(packet); }

        std::size_t offset = packet.encoded_size();

        while (offset < bytes.size()) {
            const std::size_t start = offset;

            // A frame the bytes do not hold in full is the caller's tail, not a fault: stop short of
            // it and leave it out of what this read took.
            if (bytes.size() - offset < ServerFrame::minimum_size) { break; }

            const ServerFrame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            const std::size_t frame_size = wire::count(frame.server_packet_header().packet_length()) + 2;
            if (frame_size < ServerFrame::minimum_size) { throw DecodeError(ServerPacket::name, ServerFrame::minimum_size, frame_size); }
            if (start + frame_size > bytes.size()) { offset = start; break; }
            dispatch(frame, bytes.subspan(offset, start + frame_size - offset), handler);
            offset = start + frame_size;
        }

        return offset;
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const ServerFrame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.server_packet_header().server_packet_type()) {
            case ServerPacketType::DebugPacket: return handle<ServerPayloadDebugPacket>(body, handler);
            case ServerPacketType::LoginAcceptedPacket: return handle<LoginAcceptedPacket>(body, handler);
            case ServerPacketType::LoginRejectedPacket: return handle<LoginRejectedPacket>(body, handler);
            case ServerPacketType::SequencedDataPacket: return handle<SequencedDataPacket>(body, handler);
            default:
                if constexpr (requires { handler.on_unknown(frame.server_packet_header().server_packet_type(), body); }) { handler.on_unknown(frame.server_packet_header().server_packet_type(), body); }
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

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
