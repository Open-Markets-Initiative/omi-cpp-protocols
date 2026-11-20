// Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3: PacketReader.hpp
#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"
#include "structs/SequencedMessage.hpp"
#include "enums/TemplateId.hpp"
#include "messages/InstrumentDirectoryMessage.hpp"
#include "messages/RegShoRestrictionMessage.hpp"
#include "messages/SecurityTradingStatusMessage.hpp"
#include "messages/TradingSessionStatusMessage.hpp"
#include "messages/OrderAddedMessage.hpp"
#include "messages/OrderDeletedMessage.hpp"
#include "messages/OrderReducedMessage.hpp"
#include "messages/OrderExecutedMessage.hpp"
#include "messages/TradeMessage.hpp"
#include "messages/BrokenTradeMessage.hpp"
#include "messages/CorrectedTradeMessage.hpp"
#include "messages/ClearBookMessage.hpp"
#include "messages/SnapshotCompleteMessage.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

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
        if (static_cast<std::uint8_t>(packet.common_header().message_type()) == 0) { return packet.encoded_size(); }

        // Session Shutdown: the packet carries no messages
        if (static_cast<std::uint8_t>(packet.common_header().message_type()) == 1) { return packet.encoded_size(); }

        std::size_t offset = packet.encoded_size();

        // Sequenced Message: the packet's frames; a packet selecting none of its alternatives is not read
        if (!(static_cast<std::uint8_t>(packet.common_header().message_type()) == 2)) { throw DecodeError(Packet::name, "no alternative of its Sequenced Messages is selected"); }

        // the fields its Sequenced Message holds before its frames
        wire::require(SequencedMessage::name, offset + SequencedMessage::minimum_size, bytes.size());
        const SequencedMessage sequenced_message{ bytes.subspan(offset) };
        offset += sequenced_message.encoded_size();
        const std::size_t count = wire::count(sequenced_message.message_count());

        for (std::size_t index = 0; index < count; ++index) {
            const std::size_t start = offset;
            wire::require(Frame::name, offset + Frame::minimum_size, bytes.size());
            const Frame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            const std::size_t frame_size = wire::count(frame.message_length()) + 2;
            wire::require(Packet::name, start + frame_size, bytes.size());
            dispatch(frame, bytes.subspan(offset, start + frame_size - offset), handler);
            offset = start + frame_size;
        }

        return offset;
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const Frame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.sbe_header().template_id()) {
            case TemplateId::InstrumentDirectoryMessage: return handle<InstrumentDirectoryMessage>(body, handler);
            case TemplateId::RegShoRestrictionMessage: return handle<RegShoRestrictionMessage>(body, handler);
            case TemplateId::SecurityTradingStatusMessage: return handle<SecurityTradingStatusMessage>(body, handler);
            case TemplateId::TradingSessionStatusMessage: return handle<TradingSessionStatusMessage>(body, handler);
            case TemplateId::OrderAddedMessage: return handle<OrderAddedMessage>(body, handler);
            case TemplateId::OrderDeletedMessage: return handle<OrderDeletedMessage>(body, handler);
            case TemplateId::OrderReducedMessage: return handle<OrderReducedMessage>(body, handler);
            case TemplateId::OrderExecutedMessage: return handle<OrderExecutedMessage>(body, handler);
            case TemplateId::TradeMessage: return handle<TradeMessage>(body, handler);
            case TemplateId::BrokenTradeMessage: return handle<BrokenTradeMessage>(body, handler);
            case TemplateId::CorrectedTradeMessage: return handle<CorrectedTradeMessage>(body, handler);
            case TemplateId::ClearBookMessage: return handle<ClearBookMessage>(body, handler);
            case TemplateId::SnapshotCompleteMessage: return handle<SnapshotCompleteMessage>(body, handler);
            default:
                if constexpr (requires { handler.on_unknown(frame.sbe_header().template_id(), body); }) { handler.on_unknown(frame.sbe_header().template_id(), body); }
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

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
