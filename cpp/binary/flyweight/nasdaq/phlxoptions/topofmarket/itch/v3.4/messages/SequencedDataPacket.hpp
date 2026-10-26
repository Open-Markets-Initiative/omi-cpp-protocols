#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SequencedMessageType.hpp"
#include "../messages/TimestampMessage.hpp"
#include "../messages/SystemEventMessage.hpp"
#include "../messages/OptionsDirectoryMessage.hpp"
#include "../messages/TradingActionMessage.hpp"
#include "../messages/SecurityOpenClosedMessage.hpp"
#include "../messages/ShortBestBidAndAskUpdateMessage.hpp"
#include "../messages/LongBestBidAndAskUpdateMessage.hpp"
#include "../messages/ShortBestAskUpdateMessage.hpp"
#include "../messages/ShortBestBidUpdateMessage.hpp"
#include "../messages/LongBestAskUpdateMessage.hpp"
#include "../messages/LongBestBidUpdateMessage.hpp"
#include "../messages/TradeReportMessage.hpp"
#include "../messages/BrokenTradeReportMessage.hpp"
#include "../messages/EndOfReplaySequenceMessage.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// The Sequenced Data Packets act as an envelope to carry the actual sequenced data messages
// that are transferred from the server to the client. Each Sequenced Data Packet carries one
// message from the higher-lever protocol
class SequencedDataPacket {
  public:
    static constexpr const char* name = "SequencedDataPacket";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SequencedDataPacket(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SequencedDataPacket has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return sequenced_message_end(); }

    SequencedMessageType sequenced_message_type() const { return static_cast<SequencedMessageType>(wire::read_char(at(0))); }

    // the bytes the message it selects is read from
    std::span<const std::byte> sequenced_message_bytes() const {
        wire::require("SequencedDataPacket", 1, bytes_.size());
        return bytes_.subspan(1);
    }

    // the message its sequenced_message_type selects, handed to the handler as its view
    template <typename Handler>
    void sequenced_message(Handler& handler) const {
        const auto bytes = sequenced_message_bytes();
        switch (sequenced_message_type()) {
            case SequencedMessageType::TimestampMessage: {
                wire::require(TimestampMessage::name, TimestampMessage::minimum_size, bytes.size());
                const TimestampMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::SystemEventMessage: {
                wire::require(SystemEventMessage::name, SystemEventMessage::minimum_size, bytes.size());
                const SystemEventMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::OptionsDirectoryMessage: {
                wire::require(OptionsDirectoryMessage::name, OptionsDirectoryMessage::minimum_size, bytes.size());
                const OptionsDirectoryMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::TradingActionMessage: {
                wire::require(TradingActionMessage::name, TradingActionMessage::minimum_size, bytes.size());
                const TradingActionMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::SecurityOpenClosedMessage: {
                wire::require(SecurityOpenClosedMessage::name, SecurityOpenClosedMessage::minimum_size, bytes.size());
                const SecurityOpenClosedMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::ShortBestBidAndAskUpdateMessage: {
                wire::require(ShortBestBidAndAskUpdateMessage::name, ShortBestBidAndAskUpdateMessage::minimum_size, bytes.size());
                const ShortBestBidAndAskUpdateMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::LongBestBidAndAskUpdateMessage: {
                wire::require(LongBestBidAndAskUpdateMessage::name, LongBestBidAndAskUpdateMessage::minimum_size, bytes.size());
                const LongBestBidAndAskUpdateMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::ShortBestAskUpdateMessage: {
                wire::require(ShortBestAskUpdateMessage::name, ShortBestAskUpdateMessage::minimum_size, bytes.size());
                const ShortBestAskUpdateMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::ShortBestBidUpdateMessage: {
                wire::require(ShortBestBidUpdateMessage::name, ShortBestBidUpdateMessage::minimum_size, bytes.size());
                const ShortBestBidUpdateMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::LongBestAskUpdateMessage: {
                wire::require(LongBestAskUpdateMessage::name, LongBestAskUpdateMessage::minimum_size, bytes.size());
                const LongBestAskUpdateMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::LongBestBidUpdateMessage: {
                wire::require(LongBestBidUpdateMessage::name, LongBestBidUpdateMessage::minimum_size, bytes.size());
                const LongBestBidUpdateMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::TradeReportMessage: {
                wire::require(TradeReportMessage::name, TradeReportMessage::minimum_size, bytes.size());
                const TradeReportMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::BrokenTradeReportMessage: {
                wire::require(BrokenTradeReportMessage::name, BrokenTradeReportMessage::minimum_size, bytes.size());
                const BrokenTradeReportMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case SequencedMessageType::EndOfReplaySequenceMessage: {
                wire::require(EndOfReplaySequenceMessage::name, EndOfReplaySequenceMessage::minimum_size, bytes.size());
                const EndOfReplaySequenceMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(sequenced_message_type(), bytes); }) { handler.on_unknown(sequenced_message_type(), bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t sequenced_message_size() const {
        const auto bytes = sequenced_message_bytes();
        switch (sequenced_message_type()) {
            case SequencedMessageType::TimestampMessage: return TimestampMessage{ bytes }.encoded_size();
            case SequencedMessageType::SystemEventMessage: return SystemEventMessage{ bytes }.encoded_size();
            case SequencedMessageType::OptionsDirectoryMessage: return OptionsDirectoryMessage{ bytes }.encoded_size();
            case SequencedMessageType::TradingActionMessage: return TradingActionMessage{ bytes }.encoded_size();
            case SequencedMessageType::SecurityOpenClosedMessage: return SecurityOpenClosedMessage{ bytes }.encoded_size();
            case SequencedMessageType::ShortBestBidAndAskUpdateMessage: return ShortBestBidAndAskUpdateMessage{ bytes }.encoded_size();
            case SequencedMessageType::LongBestBidAndAskUpdateMessage: return LongBestBidAndAskUpdateMessage{ bytes }.encoded_size();
            case SequencedMessageType::ShortBestAskUpdateMessage: return ShortBestAskUpdateMessage{ bytes }.encoded_size();
            case SequencedMessageType::ShortBestBidUpdateMessage: return ShortBestBidUpdateMessage{ bytes }.encoded_size();
            case SequencedMessageType::LongBestAskUpdateMessage: return LongBestAskUpdateMessage{ bytes }.encoded_size();
            case SequencedMessageType::LongBestBidUpdateMessage: return LongBestBidUpdateMessage{ bytes }.encoded_size();
            case SequencedMessageType::TradeReportMessage: return TradeReportMessage{ bytes }.encoded_size();
            case SequencedMessageType::BrokenTradeReportMessage: return BrokenTradeReportMessage{ bytes }.encoded_size();
            case SequencedMessageType::EndOfReplaySequenceMessage: return EndOfReplaySequenceMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void sequenced_message_print(std::ostream& out) const {
        const auto bytes = sequenced_message_bytes();
        switch (sequenced_message_type()) {
            case SequencedMessageType::TimestampMessage: TimestampMessage{ bytes }.print(out); return;
            case SequencedMessageType::SystemEventMessage: SystemEventMessage{ bytes }.print(out); return;
            case SequencedMessageType::OptionsDirectoryMessage: OptionsDirectoryMessage{ bytes }.print(out); return;
            case SequencedMessageType::TradingActionMessage: TradingActionMessage{ bytes }.print(out); return;
            case SequencedMessageType::SecurityOpenClosedMessage: SecurityOpenClosedMessage{ bytes }.print(out); return;
            case SequencedMessageType::ShortBestBidAndAskUpdateMessage: ShortBestBidAndAskUpdateMessage{ bytes }.print(out); return;
            case SequencedMessageType::LongBestBidAndAskUpdateMessage: LongBestBidAndAskUpdateMessage{ bytes }.print(out); return;
            case SequencedMessageType::ShortBestAskUpdateMessage: ShortBestAskUpdateMessage{ bytes }.print(out); return;
            case SequencedMessageType::ShortBestBidUpdateMessage: ShortBestBidUpdateMessage{ bytes }.print(out); return;
            case SequencedMessageType::LongBestAskUpdateMessage: LongBestAskUpdateMessage{ bytes }.print(out); return;
            case SequencedMessageType::LongBestBidUpdateMessage: LongBestBidUpdateMessage{ bytes }.print(out); return;
            case SequencedMessageType::TradeReportMessage: TradeReportMessage{ bytes }.print(out); return;
            case SequencedMessageType::BrokenTradeReportMessage: BrokenTradeReportMessage{ bytes }.print(out); return;
            case SequencedMessageType::EndOfReplaySequenceMessage: EndOfReplaySequenceMessage{ bytes }.print(out); return;
            default:
                out << "UnknownSequencedMessage{type=" << sequenced_message_type() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "SequencedDataPacket{";
        out << "sequenced_message_type=";
        out << sequenced_message_type();
        out << ", sequenced_message=";
        sequenced_message_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t sequenced_message_end() const { return 1 + sequenced_message_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SequencedDataPacket& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
