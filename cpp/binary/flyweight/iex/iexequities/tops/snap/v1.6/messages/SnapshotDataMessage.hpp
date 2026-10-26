#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/IextpHeader.hpp"
#include "../enums/IexTpMessageType.hpp"
#include "../messages/SystemEventMessage.hpp"
#include "../messages/SecurityDirectoryMessage.hpp"
#include "../messages/TradingStatusMessage.hpp"
#include "../messages/RetailLiquidityIndicatorMessage.hpp"
#include "../messages/OperationalHaltStatusMessage.hpp"
#include "../messages/ShortSalePriceTestStatusMessage.hpp"
#include "../messages/QuoteUpdateMessage.hpp"
#include "../messages/TradeReportMessage.hpp"
#include "../messages/OfficialPriceMessage.hpp"
#include "../messages/TradeBreakMessage.hpp"
#include "../messages/AuctionInformationMessage.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

// Carries one complete Tops feed message wrapped with an IexTp header providing Tops feed
// sequencing and timing information
class SnapshotDataMessage {
  public:
    static constexpr const char* name = "SnapshotDataMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SnapshotDataMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SnapshotDataMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 45;
    std::size_t encoded_size() const { return iex_tp_message_data_end(); }

    IextpHeader iextp_header() const { return IextpHeader{ bytes_.subspan(0) }; }

    std::uint16_t iex_tp_message_block_length() const { return wire::read_u16_le(at(40)); }

    std::uint16_t iex_tp_message_length() const { return wire::read_u16_le(at(42)); }

    IexTpMessageType iex_tp_message_type() const { return static_cast<IexTpMessageType>(wire::read_char(at(44))); }

    // the bytes the message it selects is read from
    std::span<const std::byte> iex_tp_message_data_bytes() const {
        const std::size_t bounded = wire::count(iex_tp_message_length());
        wire::require("SnapshotDataMessage", 45 + bounded, bytes_.size());
        return bytes_.subspan(45, bounded);
    }

    // the message its iex_tp_message_type selects, handed to the handler as its view
    template <typename Handler>
    void iex_tp_message_data(Handler& handler) const {
        const auto bytes = iex_tp_message_data_bytes();
        switch (iex_tp_message_type()) {
            case IexTpMessageType::SystemEventMessage: {
                wire::require(SystemEventMessage::name, SystemEventMessage::minimum_size, bytes.size());
                const SystemEventMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case IexTpMessageType::SecurityDirectoryMessage: {
                wire::require(SecurityDirectoryMessage::name, SecurityDirectoryMessage::minimum_size, bytes.size());
                const SecurityDirectoryMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case IexTpMessageType::TradingStatusMessage: {
                wire::require(TradingStatusMessage::name, TradingStatusMessage::minimum_size, bytes.size());
                const TradingStatusMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case IexTpMessageType::RetailLiquidityIndicatorMessage: {
                wire::require(RetailLiquidityIndicatorMessage::name, RetailLiquidityIndicatorMessage::minimum_size, bytes.size());
                const RetailLiquidityIndicatorMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case IexTpMessageType::OperationalHaltStatusMessage: {
                wire::require(OperationalHaltStatusMessage::name, OperationalHaltStatusMessage::minimum_size, bytes.size());
                const OperationalHaltStatusMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case IexTpMessageType::ShortSalePriceTestStatusMessage: {
                wire::require(ShortSalePriceTestStatusMessage::name, ShortSalePriceTestStatusMessage::minimum_size, bytes.size());
                const ShortSalePriceTestStatusMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case IexTpMessageType::QuoteUpdateMessage: {
                wire::require(QuoteUpdateMessage::name, QuoteUpdateMessage::minimum_size, bytes.size());
                const QuoteUpdateMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case IexTpMessageType::TradeReportMessage: {
                wire::require(TradeReportMessage::name, TradeReportMessage::minimum_size, bytes.size());
                const TradeReportMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case IexTpMessageType::OfficialPriceMessage: {
                wire::require(OfficialPriceMessage::name, OfficialPriceMessage::minimum_size, bytes.size());
                const OfficialPriceMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case IexTpMessageType::TradeBreakMessage: {
                wire::require(TradeBreakMessage::name, TradeBreakMessage::minimum_size, bytes.size());
                const TradeBreakMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case IexTpMessageType::AuctionInformationMessage: {
                wire::require(AuctionInformationMessage::name, AuctionInformationMessage::minimum_size, bytes.size());
                const AuctionInformationMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(iex_tp_message_type(), bytes); }) { handler.on_unknown(iex_tp_message_type(), bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t iex_tp_message_data_size() const {
        return wire::count(iex_tp_message_length());
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void iex_tp_message_data_print(std::ostream& out) const {
        const auto bytes = iex_tp_message_data_bytes();
        switch (iex_tp_message_type()) {
            case IexTpMessageType::SystemEventMessage: SystemEventMessage{ bytes }.print(out); return;
            case IexTpMessageType::SecurityDirectoryMessage: SecurityDirectoryMessage{ bytes }.print(out); return;
            case IexTpMessageType::TradingStatusMessage: TradingStatusMessage{ bytes }.print(out); return;
            case IexTpMessageType::RetailLiquidityIndicatorMessage: RetailLiquidityIndicatorMessage{ bytes }.print(out); return;
            case IexTpMessageType::OperationalHaltStatusMessage: OperationalHaltStatusMessage{ bytes }.print(out); return;
            case IexTpMessageType::ShortSalePriceTestStatusMessage: ShortSalePriceTestStatusMessage{ bytes }.print(out); return;
            case IexTpMessageType::QuoteUpdateMessage: QuoteUpdateMessage{ bytes }.print(out); return;
            case IexTpMessageType::TradeReportMessage: TradeReportMessage{ bytes }.print(out); return;
            case IexTpMessageType::OfficialPriceMessage: OfficialPriceMessage{ bytes }.print(out); return;
            case IexTpMessageType::TradeBreakMessage: TradeBreakMessage{ bytes }.print(out); return;
            case IexTpMessageType::AuctionInformationMessage: AuctionInformationMessage{ bytes }.print(out); return;
            default:
                out << "UnknownIexTpMessageData{type=" << iex_tp_message_type() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "SnapshotDataMessage{";
        out << "iextp_header=";
        iextp_header().print(out);
        out << ", iex_tp_message_block_length=";
        out << iex_tp_message_block_length();
        out << ", iex_tp_message_length=";
        out << iex_tp_message_length();
        out << ", iex_tp_message_type=";
        out << iex_tp_message_type();
        out << ", iex_tp_message_data=";
        iex_tp_message_data_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t iex_tp_message_data_end() const { return 45 + iex_tp_message_data_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SnapshotDataMessage& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::tops::snap::v1_6
