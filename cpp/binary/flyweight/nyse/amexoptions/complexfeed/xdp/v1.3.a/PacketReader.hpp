#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"
#include "enums/MessageType.hpp"
#include "messages/ComplexQuoteMessage.hpp"
#include "messages/ComplexTradeMessage.hpp"
#include "messages/ComplexCrossingRfqMessage.hpp"
#include "messages/ComplexCubeRfqMessage.hpp"
#include "messages/ComplexStatusMessage.hpp"
#include "messages/RefreshComplexQuoteMessage.hpp"
#include "messages/RefreshComplexTradeMessage.hpp"
#include "messages/ComplexSymbolDefinitionMessage.hpp"
#include "messages/StreamIdMessage.hpp"
#include "messages/SequenceNumberResetMessage.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

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
            case MessageType::ComplexQuoteMessage: return handle<ComplexQuoteMessage>(body, handler);
            case MessageType::ComplexTradeMessage: return handle<ComplexTradeMessage>(body, handler);
            case MessageType::ComplexCrossingRfqMessage: return handle<ComplexCrossingRfqMessage>(body, handler);
            case MessageType::ComplexCubeRfqMessage: return handle<ComplexCubeRfqMessage>(body, handler);
            case MessageType::ComplexStatusMessage: return handle<ComplexStatusMessage>(body, handler);
            case MessageType::RefreshComplexQuoteMessage: return handle<RefreshComplexQuoteMessage>(body, handler);
            case MessageType::RefreshComplexTradeMessage: return handle<RefreshComplexTradeMessage>(body, handler);
            case MessageType::ComplexSymbolDefinitionMessage: return handle<ComplexSymbolDefinitionMessage>(body, handler);
            case MessageType::StreamIdMessage: return handle<StreamIdMessage>(body, handler);
            case MessageType::SequenceNumberResetMessage: return handle<SequenceNumberResetMessage>(body, handler);
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

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
