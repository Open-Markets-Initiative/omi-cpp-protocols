#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/UdpPacket.hpp"
#include "structs/Frame.hpp"
#include "enums/MessageType.hpp"
#include "messages/SecondsTimestampMessage.hpp"
#include "messages/TradingStatusMessage.hpp"
#include "messages/ExecutionSummaryMessage.hpp"
#include "messages/AddOrderMessage.hpp"
#include "messages/OrderExecutedMessage.hpp"
#include "messages/OrderExecutedWithPriceMessage.hpp"
#include "messages/OrderDeleteMessage.hpp"
#include "messages/ResetMessage.hpp"
#include "messages/CommunicationControlMessage.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

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
        const std::size_t count = wire::count(packet.packet_header().message_count());

        for (std::size_t index = 0; index < count; ++index) {
            const std::size_t start = offset;
            wire::require(Frame::name, offset + Frame::minimum_size, bytes.size());
            const Frame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            const std::size_t frame_size = wire::count(frame.message_header().tag_length()) + 1;
            wire::require(UdpPacket::name, start + frame_size, bytes.size());
            dispatch(frame, bytes.subspan(offset, start + frame_size - offset), handler);
            offset = start + frame_size;
        }

        return offset;
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const Frame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.message_header().message_type()) {
            case MessageType::SecondsTimestampMessage: return handle<SecondsTimestampMessage>(body, handler);
            case MessageType::TradingStatusMessage: return handle<TradingStatusMessage>(body, handler);
            case MessageType::ExecutionSummaryMessage: return handle<ExecutionSummaryMessage>(body, handler);
            case MessageType::AddOrderMessage: return handle<AddOrderMessage>(body, handler);
            case MessageType::OrderExecutedMessage: return handle<OrderExecutedMessage>(body, handler);
            case MessageType::OrderExecutedWithPriceMessage: return handle<OrderExecutedWithPriceMessage>(body, handler);
            case MessageType::OrderDeleteMessage: return handle<OrderDeleteMessage>(body, handler);
            case MessageType::ResetMessage: return handle<ResetMessage>(body, handler);
            case MessageType::CommunicationControlMessage: return handle<CommunicationControlMessage>(body, handler);
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

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
