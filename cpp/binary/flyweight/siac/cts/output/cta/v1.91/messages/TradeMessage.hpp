#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/TradeMessageType.hpp"
#include "../messages/AuctionStatusMessage.hpp"
#include "../messages/TradeCorrectionMessage.hpp"
#include "../messages/LongTradeMessage.hpp"
#include "../messages/TradingStatusMessage.hpp"
#include "../messages/ShortTradeMessage.hpp"
#include "../messages/TradeCancelErrorMessage.hpp"

namespace siac::cts::output::cta::v1_91 {

// Trade Messages
class TradeMessage {
  public:
    static constexpr const char* name = "TradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return trade_message_payload_end(); }

    TradeMessageType trade_message_type() const { return static_cast<TradeMessageType>(wire::read_char(at(0))); }

    // the bytes the message it selects is read from
    std::span<const std::byte> trade_message_payload_bytes() const {
        wire::require("TradeMessage", 1, bytes_.size());
        return bytes_.subspan(1);
    }

    // the message its trade_message_type selects, handed to the handler as its view
    template <typename Handler>
    void trade_message_payload(Handler& handler) const {
        const auto bytes = trade_message_payload_bytes();
        switch (trade_message_type()) {
            case TradeMessageType::AuctionStatusMessage: {
                wire::require(AuctionStatusMessage::name, AuctionStatusMessage::minimum_size, bytes.size());
                const AuctionStatusMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TradeMessageType::TradeCorrectionMessage: {
                wire::require(TradeCorrectionMessage::name, TradeCorrectionMessage::minimum_size, bytes.size());
                const TradeCorrectionMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TradeMessageType::LongTradeMessage: {
                wire::require(LongTradeMessage::name, LongTradeMessage::minimum_size, bytes.size());
                const LongTradeMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TradeMessageType::TradingStatusMessage: {
                wire::require(TradingStatusMessage::name, TradingStatusMessage::minimum_size, bytes.size());
                const TradingStatusMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TradeMessageType::ShortTradeMessage: {
                wire::require(ShortTradeMessage::name, ShortTradeMessage::minimum_size, bytes.size());
                const ShortTradeMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case TradeMessageType::TradeCancelErrorMessage: {
                wire::require(TradeCancelErrorMessage::name, TradeCancelErrorMessage::minimum_size, bytes.size());
                const TradeCancelErrorMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(trade_message_type(), bytes); }) { handler.on_unknown(trade_message_type(), bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t trade_message_payload_size() const {
        const auto bytes = trade_message_payload_bytes();
        switch (trade_message_type()) {
            case TradeMessageType::AuctionStatusMessage: return AuctionStatusMessage{ bytes }.encoded_size();
            case TradeMessageType::TradeCorrectionMessage: return TradeCorrectionMessage{ bytes }.encoded_size();
            case TradeMessageType::LongTradeMessage: return LongTradeMessage{ bytes }.encoded_size();
            case TradeMessageType::TradingStatusMessage: return TradingStatusMessage{ bytes }.encoded_size();
            case TradeMessageType::ShortTradeMessage: return ShortTradeMessage{ bytes }.encoded_size();
            case TradeMessageType::TradeCancelErrorMessage: return TradeCancelErrorMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void trade_message_payload_print(std::ostream& out) const {
        const auto bytes = trade_message_payload_bytes();
        switch (trade_message_type()) {
            case TradeMessageType::AuctionStatusMessage: AuctionStatusMessage{ bytes }.print(out); return;
            case TradeMessageType::TradeCorrectionMessage: TradeCorrectionMessage{ bytes }.print(out); return;
            case TradeMessageType::LongTradeMessage: LongTradeMessage{ bytes }.print(out); return;
            case TradeMessageType::TradingStatusMessage: TradingStatusMessage{ bytes }.print(out); return;
            case TradeMessageType::ShortTradeMessage: ShortTradeMessage{ bytes }.print(out); return;
            case TradeMessageType::TradeCancelErrorMessage: TradeCancelErrorMessage{ bytes }.print(out); return;
            default:
                out << "UnknownTradeMessagePayload{type=" << trade_message_type() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "TradeMessage{";
        out << "trade_message_type=";
        out << trade_message_type();
        out << ", trade_message_payload=";
        trade_message_payload_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t trade_message_payload_end() const { return 1 + trade_message_payload_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v1_91
