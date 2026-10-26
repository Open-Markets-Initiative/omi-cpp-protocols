#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/UdpPacket.hpp"
#include "structs/Frame.hpp"
#include "enums/PacketType.hpp"
#include "messages/ApplicationMessage.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Reads a Udp Packet in place: its headers, then each message its frames carry, handed to the
// handler as a view of its bytes. A handler declares an on() for each view it wants; a view it
// declares none for is passed over, and a code no message answers to goes to on_unknown(code,
// body) when it declares one.
struct UdpPacketReader {
    // Read one packet; what it returns is how many of the bytes the packet took.
    template <typename Handler>
    static std::size_t read(std::span<const std::byte> bytes, Handler& handler) {
        wire::require(UdpPacket::name, UdpPacket::minimum_size, bytes.size());
        const UdpPacket packet{ bytes };
        if constexpr (requires { handler.on(packet); }) { handler.on(packet); }

        std::size_t offset = packet.encoded_size();

        while (offset < bytes.size()) {
            const std::size_t start = offset;
            wire::require(Frame::name, offset + Frame::minimum_size, bytes.size());
            const Frame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            const std::size_t frame_size = wire::count(frame.mach_packet_header().packet_length());
            wire::require(UdpPacket::name, start + frame_size, bytes.size());
            dispatch(frame, bytes.subspan(offset, start + frame_size - offset), handler);
            offset = start + frame_size;
        }

        return offset;
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const Frame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.mach_packet_header().packet_type()) {
            case PacketType::ApplicationMessage: return handle<ApplicationMessage>(body, handler);
            default:
                if constexpr (requires { handler.on_unknown(frame.mach_packet_header().packet_type(), body); }) { handler.on_unknown(frame.mach_packet_header().packet_type(), body); }
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

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
