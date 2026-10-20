#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"
#include "enums/MessageType.hpp"
#include "messages/SystemEventMessage.hpp"
#include "messages/SecurityDirectoryMessage.hpp"
#include "messages/TradingStatusMessage.hpp"
#include "messages/RetailLiquidityIndicatorMessage.hpp"
#include "messages/OperationalHaltStatusMessage.hpp"
#include "messages/ShortSalePriceTestStatusMessage.hpp"
#include "messages/SecurityEventMessage.hpp"
#include "messages/AddOrderMessage.hpp"
#include "messages/OrderModifyMessage.hpp"
#include "messages/OrderDeleteMessage.hpp"
#include "messages/OrderExecutedMessage.hpp"
#include "messages/TradeMessage.hpp"
#include "messages/TradeBreakMessage.hpp"
#include "messages/ClearBookMessage.hpp"

namespace iex::iexequities::deepplus::iextp::v1_05 {

// Reads a Packet in place: its headers, then each message its frames carry, handed to the
// handler as a view of its bytes. A handler declares an on() for each view it wants; a view it
// declares none for is passed over, and a code no message answers to goes to on_unknown() when
// it declares one.
struct PacketReader {
    // Read one packet; what it returns is how many of the bytes the packet took.
    template <typename Handler>
    static std::size_t read(std::span<const std::byte> bytes, Handler& handler) {
        wire::require(Packet::name, Packet::minimum_size, bytes.size());
        const Packet packet{ bytes };
        if constexpr (requires { handler.on(packet); }) { handler.on(packet); }

        // Heartbeat: the packet carries no messages
        if (packet.iextp_header().message_count() == 0) { return packet.encoded_size(); }

        std::size_t offset = packet.encoded_size();
        const std::size_t count = static_cast<std::size_t>(packet.iextp_header().message_count());

        for (std::size_t index = 0; index < count; ++index) {
            const std::size_t start = offset;
            wire::require(Frame::name, offset + Frame::minimum_size, bytes.size());
            const Frame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            const std::size_t frame_size = static_cast<std::size_t>(frame.message_header().message_length()) + 2;
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
            case MessageType::SystemEventMessage: return handle<SystemEventMessage>(body, handler);
            case MessageType::SecurityDirectoryMessage: return handle<SecurityDirectoryMessage>(body, handler);
            case MessageType::TradingStatusMessage: return handle<TradingStatusMessage>(body, handler);
            case MessageType::RetailLiquidityIndicatorMessage: return handle<RetailLiquidityIndicatorMessage>(body, handler);
            case MessageType::OperationalHaltStatusMessage: return handle<OperationalHaltStatusMessage>(body, handler);
            case MessageType::ShortSalePriceTestStatusMessage: return handle<ShortSalePriceTestStatusMessage>(body, handler);
            case MessageType::SecurityEventMessage: return handle<SecurityEventMessage>(body, handler);
            case MessageType::AddOrderMessage: return handle<AddOrderMessage>(body, handler);
            case MessageType::OrderModifyMessage: return handle<OrderModifyMessage>(body, handler);
            case MessageType::OrderDeleteMessage: return handle<OrderDeleteMessage>(body, handler);
            case MessageType::OrderExecutedMessage: return handle<OrderExecutedMessage>(body, handler);
            case MessageType::TradeMessage: return handle<TradeMessage>(body, handler);
            case MessageType::TradeBreakMessage: return handle<TradeBreakMessage>(body, handler);
            case MessageType::ClearBookMessage: return handle<ClearBookMessage>(body, handler);
            default:
                if constexpr (requires { handler.on_unknown(frame.message_header().message_type(), body); }) { handler.on_unknown(frame.message_header().message_type(), body); }
                return body.size();
        }
    }

    template <typename Message, typename Handler>
    static std::size_t handle(std::span<const std::byte> body, Handler& handler) {
        wire::require(Message::name, Message::minimum_size, body.size());
        const Message message{ body };
        if constexpr (requires { handler.on(message); }) { handler.on(message); }
        return message.encoded_size();
    }
};

} // namespace iex::iexequities::deepplus::iextp::v1_05
