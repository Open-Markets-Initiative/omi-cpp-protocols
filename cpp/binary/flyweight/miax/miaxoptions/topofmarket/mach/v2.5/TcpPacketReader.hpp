#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/TcpPacket.hpp"
#include "structs/TcpFrame.hpp"
#include "enums/SesmPacketType.hpp"
#include "messages/SequencedDataPacket.hpp"
#include "messages/UnsequencedDataPacket.hpp"
#include "messages/LoginRequest.hpp"
#include "messages/LoginResponse.hpp"
#include "messages/SynchronizationComplete.hpp"
#include "messages/RetransmissionRequest.hpp"
#include "messages/LogoutRequest.hpp"
#include "messages/GoodbyePacket.hpp"
#include "messages/TestPacket.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

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

        std::size_t offset = packet.encoded_size();

        while (offset < bytes.size()) {
            const std::size_t start = offset;

            // A frame the bytes do not hold in full is the caller's tail, not a fault: stop short of
            // it and leave it out of what this read took.
            if (bytes.size() - offset < TcpFrame::minimum_size) { break; }

            const TcpFrame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            const std::size_t frame_size = wire::count(frame.sesm_packet_header().sesm_packet_length()) + 2;
            if (frame_size < TcpFrame::minimum_size) { throw DecodeError(TcpPacket::name, TcpFrame::minimum_size, frame_size); }
            if (start + frame_size > bytes.size()) { offset = start; break; }
            dispatch(frame, bytes.subspan(offset, start + frame_size - offset), handler);
            offset = start + frame_size;
        }

        return offset;
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const TcpFrame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.sesm_packet_header().sesm_packet_type()) {
            case SesmPacketType::SequencedDataPacket: return handle<SequencedDataPacket>(body, handler);
            case SesmPacketType::UnsequencedDataPacket: return handle<UnsequencedDataPacket>(body, handler);
            case SesmPacketType::LoginRequest: return handle<LoginRequest>(body, handler);
            case SesmPacketType::LoginResponse: return handle<LoginResponse>(body, handler);
            case SesmPacketType::SynchronizationComplete: return handle<SynchronizationComplete>(body, handler);
            case SesmPacketType::RetransmissionRequest: return handle<RetransmissionRequest>(body, handler);
            case SesmPacketType::LogoutRequest: return handle<LogoutRequest>(body, handler);
            case SesmPacketType::GoodbyePacket: return handle<GoodbyePacket>(body, handler);
            case SesmPacketType::TestPacket: return handle<TestPacket>(body, handler);
            default:
                if constexpr (requires { handler.on_unknown(frame.sesm_packet_header().sesm_packet_type(), body); }) { handler.on_unknown(frame.sesm_packet_header().sesm_packet_type(), body); }
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
