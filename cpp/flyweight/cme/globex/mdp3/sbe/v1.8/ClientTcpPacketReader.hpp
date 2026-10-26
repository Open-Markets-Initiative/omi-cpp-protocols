#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/ClientTcpPacket.hpp"
#include "structs/ClientTcpFrame.hpp"
#include "enums/TemplateId.hpp"
#include "messages/ClientPayloadNegotiate.hpp"
#include "messages/ClientPayloadTerminate.hpp"
#include "messages/ClientPayloadMarketDataRequest.hpp"
#include "messages/ClientPayloadSecurityListRequest.hpp"
#include "messages/ClientPayloadSecurityStatusRequest.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// Reads a Client Tcp Packet in place: its headers, then each message its frames carry, handed
// to the handler as a view of its bytes. A handler declares an on() for each view it wants; a
// view it declares none for is passed over, and a code no message answers to goes to
// on_unknown(code, body) when it declares one.
struct ClientTcpPacketReader {
    // Read one packet; what it returns is how many of the bytes the packet took.
    template <typename Handler>
    static std::size_t read(std::span<const std::byte> bytes, Handler& handler) {
        wire::require(ClientTcpPacket::name, ClientTcpPacket::minimum_size, bytes.size());
        const ClientTcpPacket packet{ bytes };
        if constexpr (requires { handler.on(packet); }) { handler.on(packet); }

        std::size_t offset = packet.encoded_size();

        while (offset < bytes.size()) {
            const std::size_t start = offset;

            // A frame the bytes do not hold in full is the caller's tail, not a fault: stop short of
            // it and leave it out of what this read took.
            if (bytes.size() - offset < ClientTcpFrame::minimum_size) { break; }

            const ClientTcpFrame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            const std::size_t frame_size = wire::count(frame.message_header().message_size()) + 14;
            if (frame_size < ClientTcpFrame::minimum_size) { throw DecodeError(ClientTcpPacket::name, ClientTcpFrame::minimum_size, frame_size); }
            if (start + frame_size > bytes.size()) { offset = start; break; }
            dispatch(frame, bytes.subspan(offset, start + frame_size - offset), handler);
            offset = start + frame_size;
        }

        return offset;
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const ClientTcpFrame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.message_header().simple_binary_header().template_id()) {
            case TemplateId::Negotiate: return handle<ClientPayloadNegotiate>(body, handler);
            case TemplateId::Terminate: return handle<ClientPayloadTerminate>(body, handler);
            case TemplateId::MarketDataRequest: return handle<ClientPayloadMarketDataRequest>(body, handler);
            case TemplateId::SecurityListRequest: return handle<ClientPayloadSecurityListRequest>(body, handler);
            case TemplateId::SecurityStatusRequest: return handle<ClientPayloadSecurityStatusRequest>(body, handler);
            default:
                if constexpr (requires { handler.on_unknown(frame.message_header().simple_binary_header().template_id(), body); }) { handler.on_unknown(frame.message_header().simple_binary_header().template_id(), body); }
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

} // namespace cme::globex::mdp3::sbe::v1_8
