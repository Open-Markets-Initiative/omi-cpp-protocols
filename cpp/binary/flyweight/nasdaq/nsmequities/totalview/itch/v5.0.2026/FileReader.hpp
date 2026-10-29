#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/File.hpp"
#include "structs/FileFrame.hpp"
#include "enums/MessageType.hpp"
#include "messages/FilePayloadSystemEventMessage.hpp"
#include "messages/FilePayloadStockDirectoryMessage.hpp"
#include "messages/FilePayloadStockTradingActionMessage.hpp"
#include "messages/FilePayloadRegShoShortSalePriceTestRestrictedIndicatorMessage.hpp"
#include "messages/FilePayloadMarketParticipantPositionMessage.hpp"
#include "messages/FilePayloadMwcbDeclineLevelMessage.hpp"
#include "messages/FilePayloadMwcbStatusLevelMessage.hpp"
#include "messages/FilePayloadIpoQuotingPeriodUpdate.hpp"
#include "messages/FilePayloadLuldAuctionCollarMessage.hpp"
#include "messages/FilePayloadOperationalHaltMessage.hpp"
#include "messages/FilePayloadAddOrderNoMpidAttributionMessage.hpp"
#include "messages/FilePayloadAddOrderWithMpidAttributionMessage.hpp"
#include "messages/FilePayloadOrderExecutedMessage.hpp"
#include "messages/FilePayloadOrderExecutedWithPriceMessage.hpp"
#include "messages/FilePayloadOrderCancelMessage.hpp"
#include "messages/FilePayloadOrderDeleteMessage.hpp"
#include "messages/FilePayloadOrderReplaceMessage.hpp"
#include "messages/FilePayloadNonCrossTradeMessage.hpp"
#include "messages/FilePayloadCrossTradeMessage.hpp"
#include "messages/FilePayloadBrokenTradeMessage.hpp"
#include "messages/FilePayloadNetOrderImbalanceIndicatorMessage.hpp"
#include "messages/FilePayloadRetailPriceImprovementIndicatorMessage.hpp"
#include "messages/FilePayloadDirectListingWithCapitalRaisePriceDiscoveryMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

// Reads a File in place: its headers, then each message its frames carry, handed to the
// handler as a view of its bytes. A handler declares an on() for each view it wants; a view it
// declares none for is passed over, and a code no message answers to goes to on_unknown(code,
// body) when it declares one.
struct FileReader {
    // Read one packet; what it returns is how many of the bytes the packet took.
    template <typename Handler>
    static std::size_t read(std::span<const std::byte> bytes, Handler& handler) {
        wire::require(File::name, File::minimum_size, bytes.size());
        const File packet{ bytes };
        if constexpr (requires { handler.on(packet); }) { handler.on(packet); }

        std::size_t offset = packet.encoded_size();

        while (offset < bytes.size()) {
            const std::size_t start = offset;

            // A frame the bytes do not hold in full is the caller's tail, not a fault: stop short of
            // it and leave it out of what this read took.
            if (bytes.size() - offset < FileFrame::minimum_size) { break; }

            const FileFrame frame{ bytes.subspan(offset) };
            offset += frame.encoded_size();
            const std::size_t frame_size = wire::count(frame.message_header().message_length()) + 2;
            if (frame_size < FileFrame::minimum_size) { throw DecodeError(File::name, FileFrame::minimum_size, frame_size); }
            if (start + frame_size > bytes.size()) { offset = start; break; }
            dispatch(frame, bytes.subspan(offset, start + frame_size - offset), handler);
            offset = start + frame_size;
        }

        return offset;
    }

  private:
    template <typename Handler>
    static std::size_t dispatch(const FileFrame& frame, std::span<const std::byte> body, Handler& handler) {
        switch (frame.message_header().message_type()) {
            case MessageType::SystemEventMessage: return handle<FilePayloadSystemEventMessage>(body, handler);
            case MessageType::StockDirectoryMessage: return handle<FilePayloadStockDirectoryMessage>(body, handler);
            case MessageType::StockTradingActionMessage: return handle<FilePayloadStockTradingActionMessage>(body, handler);
            case MessageType::RegShoShortSalePriceTestRestrictedIndicatorMessage: return handle<FilePayloadRegShoShortSalePriceTestRestrictedIndicatorMessage>(body, handler);
            case MessageType::MarketParticipantPositionMessage: return handle<FilePayloadMarketParticipantPositionMessage>(body, handler);
            case MessageType::MwcbDeclineLevelMessage: return handle<FilePayloadMwcbDeclineLevelMessage>(body, handler);
            case MessageType::MwcbStatusLevelMessage: return handle<FilePayloadMwcbStatusLevelMessage>(body, handler);
            case MessageType::IpoQuotingPeriodUpdate: return handle<FilePayloadIpoQuotingPeriodUpdate>(body, handler);
            case MessageType::LuldAuctionCollarMessage: return handle<FilePayloadLuldAuctionCollarMessage>(body, handler);
            case MessageType::OperationalHaltMessage: return handle<FilePayloadOperationalHaltMessage>(body, handler);
            case MessageType::AddOrderNoMpidAttributionMessage: return handle<FilePayloadAddOrderNoMpidAttributionMessage>(body, handler);
            case MessageType::AddOrderWithMpidAttributionMessage: return handle<FilePayloadAddOrderWithMpidAttributionMessage>(body, handler);
            case MessageType::OrderExecutedMessage: return handle<FilePayloadOrderExecutedMessage>(body, handler);
            case MessageType::OrderExecutedWithPriceMessage: return handle<FilePayloadOrderExecutedWithPriceMessage>(body, handler);
            case MessageType::OrderCancelMessage: return handle<FilePayloadOrderCancelMessage>(body, handler);
            case MessageType::OrderDeleteMessage: return handle<FilePayloadOrderDeleteMessage>(body, handler);
            case MessageType::OrderReplaceMessage: return handle<FilePayloadOrderReplaceMessage>(body, handler);
            case MessageType::NonCrossTradeMessage: return handle<FilePayloadNonCrossTradeMessage>(body, handler);
            case MessageType::CrossTradeMessage: return handle<FilePayloadCrossTradeMessage>(body, handler);
            case MessageType::BrokenTradeMessage: return handle<FilePayloadBrokenTradeMessage>(body, handler);
            case MessageType::NetOrderImbalanceIndicatorMessage: return handle<FilePayloadNetOrderImbalanceIndicatorMessage>(body, handler);
            case MessageType::RetailPriceImprovementIndicatorMessage: return handle<FilePayloadRetailPriceImprovementIndicatorMessage>(body, handler);
            case MessageType::DirectListingWithCapitalRaisePriceDiscoveryMessage: return handle<FilePayloadDirectListingWithCapitalRaisePriceDiscoveryMessage>(body, handler);
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

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2026
