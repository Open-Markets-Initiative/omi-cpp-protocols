#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/Packet.hpp"
#include "structs/PacketFrame.hpp"
#include "enums/MessageType.hpp"
#include "messages/UdpPayloadSystemEventMessage.hpp"
#include "messages/UdpPayloadOptionsDirectoryMessage.hpp"
#include "messages/UdpPayloadTradingActionMessage.hpp"
#include "messages/UdpPayloadSecurityOpenMessage.hpp"
#include "messages/UdpPayloadAddOrderMessageShortMessageForm.hpp"
#include "messages/UdpPayloadAddOrderMessageLongFormMessage.hpp"
#include "messages/UdpPayloadAddQuoteMessageShortFormMessage.hpp"
#include "messages/UdpPayloadAddQuoteMessageLongFormMessage.hpp"
#include "messages/UdpPayloadSingleSideExecutedMessage.hpp"
#include "messages/UdpPayloadSingleSideExecutedWithPriceMessage.hpp"
#include "messages/UdpPayloadOrderCancelMessage.hpp"
#include "messages/UdpPayloadSingleSideReplaceMessageShortForm.hpp"
#include "messages/UdpPayloadSingleSideReplaceMessageLongForm.hpp"
#include "messages/UdpPayloadSingleSideDeleteMessage.hpp"
#include "messages/UdpPayloadSingleSideChangeMessage.hpp"
#include "messages/UdpPayloadQuoteReplaceMessageShortForm.hpp"
#include "messages/UdpPayloadQuoteReplaceMessageLongForm.hpp"
#include "messages/UdpPayloadQuoteDeleteMessage.hpp"
#include "messages/UdpPayloadOptionsTradeMessagesNonAuction.hpp"
#include "messages/UdpPayloadOptionsCrossTradeMessage.hpp"
#include "messages/UdpPayloadBrokenTradeOrderExecutedMessage.hpp"
#include "messages/UdpPayloadNoiiMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

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
        if (packet.packet_header().message_count() == 0) { return packet.encoded_size(); }

        // End Of Session: the packet carries no messages
        if (packet.packet_header().message_count() == 65535) { return packet.encoded_size(); }

        std::size_t offset = packet.encoded_size();
        const std::size_t count = wire::count(packet.packet_header().message_count());

        for (std::size_t index = 0; index < count; ++index) {
            const std::size_t start = offset;
            wire::require(PacketFrame::name, offset + PacketFrame::minimum_size, bytes.size());
            const PacketFrame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            const std::size_t frame_size = wire::count(frame.message_header().message_length()) + 2;
            wire::require(Packet::name, start + frame_size, bytes.size());
            dispatch(frame, bytes.subspan(offset, start + frame_size - offset), handler);
            offset = start + frame_size;
        }

        return offset;
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const PacketFrame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.message_header().message_type()) {
            case MessageType::SystemEventMessage: return handle<UdpPayloadSystemEventMessage>(body, handler);
            case MessageType::OptionsDirectoryMessage: return handle<UdpPayloadOptionsDirectoryMessage>(body, handler);
            case MessageType::TradingActionMessage: return handle<UdpPayloadTradingActionMessage>(body, handler);
            case MessageType::SecurityOpenMessage: return handle<UdpPayloadSecurityOpenMessage>(body, handler);
            case MessageType::AddOrderMessageShortMessageForm: return handle<UdpPayloadAddOrderMessageShortMessageForm>(body, handler);
            case MessageType::AddOrderMessageLongFormMessage: return handle<UdpPayloadAddOrderMessageLongFormMessage>(body, handler);
            case MessageType::AddQuoteMessageShortFormMessage: return handle<UdpPayloadAddQuoteMessageShortFormMessage>(body, handler);
            case MessageType::AddQuoteMessageLongFormMessage: return handle<UdpPayloadAddQuoteMessageLongFormMessage>(body, handler);
            case MessageType::SingleSideExecutedMessage: return handle<UdpPayloadSingleSideExecutedMessage>(body, handler);
            case MessageType::SingleSideExecutedWithPriceMessage: return handle<UdpPayloadSingleSideExecutedWithPriceMessage>(body, handler);
            case MessageType::OrderCancelMessage: return handle<UdpPayloadOrderCancelMessage>(body, handler);
            case MessageType::SingleSideReplaceMessageShortForm: return handle<UdpPayloadSingleSideReplaceMessageShortForm>(body, handler);
            case MessageType::SingleSideReplaceMessageLongForm: return handle<UdpPayloadSingleSideReplaceMessageLongForm>(body, handler);
            case MessageType::SingleSideDeleteMessage: return handle<UdpPayloadSingleSideDeleteMessage>(body, handler);
            case MessageType::SingleSideChangeMessage: return handle<UdpPayloadSingleSideChangeMessage>(body, handler);
            case MessageType::QuoteReplaceMessageShortForm: return handle<UdpPayloadQuoteReplaceMessageShortForm>(body, handler);
            case MessageType::QuoteReplaceMessageLongForm: return handle<UdpPayloadQuoteReplaceMessageLongForm>(body, handler);
            case MessageType::QuoteDeleteMessage: return handle<UdpPayloadQuoteDeleteMessage>(body, handler);
            case MessageType::OptionsTradeMessagesNonAuction: return handle<UdpPayloadOptionsTradeMessagesNonAuction>(body, handler);
            case MessageType::OptionsCrossTradeMessage: return handle<UdpPayloadOptionsCrossTradeMessage>(body, handler);
            case MessageType::BrokenTradeOrderExecutedMessage: return handle<UdpPayloadBrokenTradeOrderExecutedMessage>(body, handler);
            case MessageType::NoiiMessage: return handle<UdpPayloadNoiiMessage>(body, handler);
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

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
