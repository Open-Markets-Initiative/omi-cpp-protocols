#pragma once

#include <cstddef>
#include <span>

#include "common/Wire.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"
#include "enums/MessageType.hpp"
#include "messages/SystemEventMessage.hpp"
#include "messages/TradeReportMessage.hpp"
#include "messages/LongFormTradeReportMessage.hpp"
#include "messages/NextSharesTradeReportMessage.hpp"
#include "messages/TradeCancelErrorMessage.hpp"
#include "messages/LongFormTradeCancelErrorMessage.hpp"
#include "messages/NextSharesTradeCancelErrorMessage.hpp"
#include "messages/TradeCorrectionMessage.hpp"
#include "messages/LongFormTradeCorrectionMessage.hpp"
#include "messages/NextSharesTradeCorrectionMessage.hpp"
#include "messages/StockTradingActionMessage.hpp"
#include "messages/StockDirectoryMessage.hpp"
#include "messages/RegShoShortSalePriceTestRestrictedIndicatorMessage.hpp"
#include "messages/AdjustedClosingPriceMessage.hpp"
#include "messages/LongFormAdjustedClosingPriceMessage.hpp"
#include "messages/EndOfDayTradeSummaryMessage.hpp"
#include "messages/LongFormEndOfDayTradeSummaryMessage.hpp"
#include "messages/NextSharesEndOfDayTradeSummaryMessage.hpp"
#include "messages/IpoInformationMessage.hpp"
#include "messages/MwcbDeclineLevelMessage.hpp"
#include "messages/MwcbStatusMessage.hpp"
#include "messages/IpoQuotingPeriodUpdateMessage.hpp"
#include "messages/OperationalHaltMessage.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

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
            case MessageType::SystemEventMessage: return handle<SystemEventMessage>(body, handler);
            case MessageType::TradeReportMessage: return handle<TradeReportMessage>(body, handler);
            case MessageType::LongFormTradeReportMessage: return handle<LongFormTradeReportMessage>(body, handler);
            case MessageType::NextSharesTradeReportMessage: return handle<NextSharesTradeReportMessage>(body, handler);
            case MessageType::TradeCancelErrorMessage: return handle<TradeCancelErrorMessage>(body, handler);
            case MessageType::LongFormTradeCancelErrorMessage: return handle<LongFormTradeCancelErrorMessage>(body, handler);
            case MessageType::NextSharesTradeCancelErrorMessage: return handle<NextSharesTradeCancelErrorMessage>(body, handler);
            case MessageType::TradeCorrectionMessage: return handle<TradeCorrectionMessage>(body, handler);
            case MessageType::LongFormTradeCorrectionMessage: return handle<LongFormTradeCorrectionMessage>(body, handler);
            case MessageType::NextSharesTradeCorrectionMessage: return handle<NextSharesTradeCorrectionMessage>(body, handler);
            case MessageType::StockTradingActionMessage: return handle<StockTradingActionMessage>(body, handler);
            case MessageType::StockDirectoryMessage: return handle<StockDirectoryMessage>(body, handler);
            case MessageType::RegShoShortSalePriceTestRestrictedIndicatorMessage: return handle<RegShoShortSalePriceTestRestrictedIndicatorMessage>(body, handler);
            case MessageType::AdjustedClosingPriceMessage: return handle<AdjustedClosingPriceMessage>(body, handler);
            case MessageType::LongFormAdjustedClosingPriceMessage: return handle<LongFormAdjustedClosingPriceMessage>(body, handler);
            case MessageType::EndOfDayTradeSummaryMessage: return handle<EndOfDayTradeSummaryMessage>(body, handler);
            case MessageType::LongFormEndOfDayTradeSummaryMessage: return handle<LongFormEndOfDayTradeSummaryMessage>(body, handler);
            case MessageType::NextSharesEndOfDayTradeSummaryMessage: return handle<NextSharesEndOfDayTradeSummaryMessage>(body, handler);
            case MessageType::IpoInformationMessage: return handle<IpoInformationMessage>(body, handler);
            case MessageType::MwcbDeclineLevelMessage: return handle<MwcbDeclineLevelMessage>(body, handler);
            case MessageType::MwcbStatusMessage: return handle<MwcbStatusMessage>(body, handler);
            case MessageType::IpoQuotingPeriodUpdateMessage: return handle<IpoQuotingPeriodUpdateMessage>(body, handler);
            case MessageType::OperationalHaltMessage: return handle<OperationalHaltMessage>(body, handler);
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

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
