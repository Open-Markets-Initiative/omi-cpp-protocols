#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/Packet.hpp"
#include "structs/PacketFrame.hpp"
#include "enums/MessageType.hpp"
#include "messages/PayloadSystemEventMessage.hpp"
#include "messages/PayloadStockDirectoryMessage.hpp"
#include "messages/PayloadStockTradingActionMessage.hpp"
#include "messages/PayloadRegShoShortSalePriceTestRestrictedIndicatorMessage.hpp"
#include "messages/PayloadMarketParticipantPositionMessage.hpp"
#include "messages/PayloadMwcbDeclineLevelMessage.hpp"
#include "messages/PayloadMwcbStatusLevelMessage.hpp"
#include "messages/PayloadIpoQuotingPeriodUpdate.hpp"
#include "messages/PayloadLuldAuctionCollarMessage.hpp"
#include "messages/PayloadOperationalHaltMessage.hpp"
#include "messages/PayloadAddOrderNoMpidAttributionMessage.hpp"
#include "messages/PayloadAddOrderWithMpidAttributionMessage.hpp"
#include "messages/PayloadOrderExecutedMessage.hpp"
#include "messages/PayloadOrderExecutedWithPriceMessage.hpp"
#include "messages/PayloadOrderCancelMessage.hpp"
#include "messages/PayloadOrderDeleteMessage.hpp"
#include "messages/PayloadOrderReplaceMessage.hpp"
#include "messages/PayloadNonCrossTradeMessage.hpp"
#include "messages/PayloadCrossTradeMessage.hpp"
#include "messages/PayloadBrokenTradeMessage.hpp"
#include "messages/PayloadNetOrderImbalanceIndicatorMessage.hpp"
#include "messages/PayloadRetailPriceImprovementIndicatorMessage.hpp"
#include "messages/PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

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
            case MessageType::SystemEventMessage: return handle<PayloadSystemEventMessage>(body, handler);
            case MessageType::StockDirectoryMessage: return handle<PayloadStockDirectoryMessage>(body, handler);
            case MessageType::StockTradingActionMessage: return handle<PayloadStockTradingActionMessage>(body, handler);
            case MessageType::RegShoShortSalePriceTestRestrictedIndicatorMessage: return handle<PayloadRegShoShortSalePriceTestRestrictedIndicatorMessage>(body, handler);
            case MessageType::MarketParticipantPositionMessage: return handle<PayloadMarketParticipantPositionMessage>(body, handler);
            case MessageType::MwcbDeclineLevelMessage: return handle<PayloadMwcbDeclineLevelMessage>(body, handler);
            case MessageType::MwcbStatusLevelMessage: return handle<PayloadMwcbStatusLevelMessage>(body, handler);
            case MessageType::IpoQuotingPeriodUpdate: return handle<PayloadIpoQuotingPeriodUpdate>(body, handler);
            case MessageType::LuldAuctionCollarMessage: return handle<PayloadLuldAuctionCollarMessage>(body, handler);
            case MessageType::OperationalHaltMessage: return handle<PayloadOperationalHaltMessage>(body, handler);
            case MessageType::AddOrderNoMpidAttributionMessage: return handle<PayloadAddOrderNoMpidAttributionMessage>(body, handler);
            case MessageType::AddOrderWithMpidAttributionMessage: return handle<PayloadAddOrderWithMpidAttributionMessage>(body, handler);
            case MessageType::OrderExecutedMessage: return handle<PayloadOrderExecutedMessage>(body, handler);
            case MessageType::OrderExecutedWithPriceMessage: return handle<PayloadOrderExecutedWithPriceMessage>(body, handler);
            case MessageType::OrderCancelMessage: return handle<PayloadOrderCancelMessage>(body, handler);
            case MessageType::OrderDeleteMessage: return handle<PayloadOrderDeleteMessage>(body, handler);
            case MessageType::OrderReplaceMessage: return handle<PayloadOrderReplaceMessage>(body, handler);
            case MessageType::NonCrossTradeMessage: return handle<PayloadNonCrossTradeMessage>(body, handler);
            case MessageType::CrossTradeMessage: return handle<PayloadCrossTradeMessage>(body, handler);
            case MessageType::BrokenTradeMessage: return handle<PayloadBrokenTradeMessage>(body, handler);
            case MessageType::NetOrderImbalanceIndicatorMessage: return handle<PayloadNetOrderImbalanceIndicatorMessage>(body, handler);
            case MessageType::RetailPriceImprovementIndicatorMessage: return handle<PayloadRetailPriceImprovementIndicatorMessage>(body, handler);
            case MessageType::DirectListingWithCapitalRaisePriceDiscoveryMessage: return handle<PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage>(body, handler);
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

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
