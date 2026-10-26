#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"
#include "enums/MessageType.hpp"
#include "messages/SecondsMessage.hpp"
#include "messages/EndOfBusinessTradeDateMessage.hpp"
#include "messages/FutureSymbolDirectoryMessage.hpp"
#include "messages/OptionsSymbolDirectoryMessage.hpp"
#include "messages/CombinationSymbolDirectoryMessage.hpp"
#include "messages/BundlesSymbolDirectory.hpp"
#include "messages/OrderBookStateMessage.hpp"
#include "messages/AddOrderMessage.hpp"
#include "messages/OrderVolumeCancelledMessage.hpp"
#include "messages/OrderDeletedMessage.hpp"
#include "messages/OrderExecutedMessage.hpp"
#include "messages/AuctionOrderExecutedMessage.hpp"
#include "messages/CombinationOrderExecutedMessage.hpp"
#include "messages/ImpliedOrderAddedMessage.hpp"
#include "messages/ImpliedOrderReplacedMessage.hpp"
#include "messages/ImpliedOrderDeletedMessage.hpp"
#include "messages/TradeExecutedMessage.hpp"
#include "messages/CombinationTradeExecutedMessage.hpp"
#include "messages/TradeCancellationMessage.hpp"
#include "messages/EquilibriumPriceMessage.hpp"
#include "messages/OpenHighLowLastTradeAdjustmentMessage.hpp"
#include "messages/MarketSettlementMessage.hpp"
#include "messages/TextMessage.hpp"
#include "messages/RequestForQuoteMessage.hpp"
#include "messages/AnomalousOrderThresholdPublishMessage.hpp"
#include "messages/VolumeAndOpenInterestMessage.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

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
            wire::require(Frame::name, offset + Frame::minimum_size, bytes.size());
            const Frame frame{ bytes.subspan(offset) };
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
    static std::size_t dispatch(const Frame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.message_header().message_type()) {
            case MessageType::SecondsMessage: return handle<SecondsMessage>(body, handler);
            case MessageType::EndOfBusinessTradeDateMessage: return handle<EndOfBusinessTradeDateMessage>(body, handler);
            case MessageType::FutureSymbolDirectoryMessage: return handle<FutureSymbolDirectoryMessage>(body, handler);
            case MessageType::OptionsSymbolDirectoryMessage: return handle<OptionsSymbolDirectoryMessage>(body, handler);
            case MessageType::CombinationSymbolDirectoryMessage: return handle<CombinationSymbolDirectoryMessage>(body, handler);
            case MessageType::BundlesSymbolDirectory: return handle<BundlesSymbolDirectory>(body, handler);
            case MessageType::OrderBookStateMessage: return handle<OrderBookStateMessage>(body, handler);
            case MessageType::AddOrderMessage: return handle<AddOrderMessage>(body, handler);
            case MessageType::OrderVolumeCancelledMessage: return handle<OrderVolumeCancelledMessage>(body, handler);
            case MessageType::OrderDeletedMessage: return handle<OrderDeletedMessage>(body, handler);
            case MessageType::OrderExecutedMessage: return handle<OrderExecutedMessage>(body, handler);
            case MessageType::AuctionOrderExecutedMessage: return handle<AuctionOrderExecutedMessage>(body, handler);
            case MessageType::CombinationOrderExecutedMessage: return handle<CombinationOrderExecutedMessage>(body, handler);
            case MessageType::ImpliedOrderAddedMessage: return handle<ImpliedOrderAddedMessage>(body, handler);
            case MessageType::ImpliedOrderReplacedMessage: return handle<ImpliedOrderReplacedMessage>(body, handler);
            case MessageType::ImpliedOrderDeletedMessage: return handle<ImpliedOrderDeletedMessage>(body, handler);
            case MessageType::TradeExecutedMessage: return handle<TradeExecutedMessage>(body, handler);
            case MessageType::CombinationTradeExecutedMessage: return handle<CombinationTradeExecutedMessage>(body, handler);
            case MessageType::TradeCancellationMessage: return handle<TradeCancellationMessage>(body, handler);
            case MessageType::EquilibriumPriceMessage: return handle<EquilibriumPriceMessage>(body, handler);
            case MessageType::OpenHighLowLastTradeAdjustmentMessage: return handle<OpenHighLowLastTradeAdjustmentMessage>(body, handler);
            case MessageType::MarketSettlementMessage: return handle<MarketSettlementMessage>(body, handler);
            case MessageType::TextMessage: return handle<TextMessage>(body, handler);
            case MessageType::RequestForQuoteMessage: return handle<RequestForQuoteMessage>(body, handler);
            case MessageType::AnomalousOrderThresholdPublishMessage: return handle<AnomalousOrderThresholdPublishMessage>(body, handler);
            case MessageType::VolumeAndOpenInterestMessage: return handle<VolumeAndOpenInterestMessage>(body, handler);
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

} // namespace asx::asxderivatives::ntp::itch::v1_05
