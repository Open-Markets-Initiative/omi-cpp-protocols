#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MessageType.hpp"
#include "../messages/SystemTimeMessage.hpp"
#include "../messages/SimpleSeriesUpdateMessage.hpp"
#include "../messages/SystemStateMessage.hpp"
#include "../messages/SimpleTopOfMarketBestBidOrOfferCompactBidMessage.hpp"
#include "../messages/SimpleTopOfMarketBestBidOrOfferCompactOfferMessage.hpp"
#include "../messages/SimpleTopOfMarketBestBidOrOfferWideBidMessage.hpp"
#include "../messages/SimpleTopOfMarketBestBidOrOfferWideOfferMessage.hpp"
#include "../messages/SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage.hpp"
#include "../messages/SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage.hpp"
#include "../messages/LastSaleMessage.hpp"
#include "../messages/TradeCancelMessage.hpp"
#include "../messages/UnderlyingTradingStatusNotificationMessage.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

class RefreshResponseMessageApplicationMessage {
  public:
    static constexpr const char* name = "RefreshResponseMessageApplicationMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RefreshResponseMessageApplicationMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RefreshResponseMessageApplicationMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return data_end(); }

    MessageType message_type() const { return static_cast<MessageType>(wire::read_char(at(0))); }

    // the bytes the message it selects is read from
    std::span<const std::byte> data_bytes() const {
        wire::require("RefreshResponseMessageApplicationMessage", 1, bytes_.size());
        return bytes_.subspan(1);
    }

    // the message its message_type selects, handed to the handler as its view
    template <typename Handler>
    void data(Handler& handler) const {
        const auto bytes = data_bytes();
        switch (message_type()) {
            case MessageType::SystemTimeMessage: {
                wire::require(SystemTimeMessage::name, SystemTimeMessage::minimum_size, bytes.size());
                const SystemTimeMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::SimpleSeriesUpdateMessage: {
                wire::require(SimpleSeriesUpdateMessage::name, SimpleSeriesUpdateMessage::minimum_size, bytes.size());
                const SimpleSeriesUpdateMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::SystemStateMessage: {
                wire::require(SystemStateMessage::name, SystemStateMessage::minimum_size, bytes.size());
                const SystemStateMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::SimpleTopOfMarketBestBidOrOfferCompactBidMessage: {
                wire::require(SimpleTopOfMarketBestBidOrOfferCompactBidMessage::name, SimpleTopOfMarketBestBidOrOfferCompactBidMessage::minimum_size, bytes.size());
                const SimpleTopOfMarketBestBidOrOfferCompactBidMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::SimpleTopOfMarketBestBidOrOfferCompactOfferMessage: {
                wire::require(SimpleTopOfMarketBestBidOrOfferCompactOfferMessage::name, SimpleTopOfMarketBestBidOrOfferCompactOfferMessage::minimum_size, bytes.size());
                const SimpleTopOfMarketBestBidOrOfferCompactOfferMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::SimpleTopOfMarketBestBidOrOfferWideBidMessage: {
                wire::require(SimpleTopOfMarketBestBidOrOfferWideBidMessage::name, SimpleTopOfMarketBestBidOrOfferWideBidMessage::minimum_size, bytes.size());
                const SimpleTopOfMarketBestBidOrOfferWideBidMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::SimpleTopOfMarketBestBidOrOfferWideOfferMessage: {
                wire::require(SimpleTopOfMarketBestBidOrOfferWideOfferMessage::name, SimpleTopOfMarketBestBidOrOfferWideOfferMessage::minimum_size, bytes.size());
                const SimpleTopOfMarketBestBidOrOfferWideOfferMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage: {
                wire::require(SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::name, SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage::minimum_size, bytes.size());
                const SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage: {
                wire::require(SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::name, SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage::minimum_size, bytes.size());
                const SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::LastSaleMessage: {
                wire::require(LastSaleMessage::name, LastSaleMessage::minimum_size, bytes.size());
                const LastSaleMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::TradeCancelMessage: {
                wire::require(TradeCancelMessage::name, TradeCancelMessage::minimum_size, bytes.size());
                const TradeCancelMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::UnderlyingTradingStatusNotificationMessage: {
                wire::require(UnderlyingTradingStatusNotificationMessage::name, UnderlyingTradingStatusNotificationMessage::minimum_size, bytes.size());
                const UnderlyingTradingStatusNotificationMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(message_type(), bytes); }) { handler.on_unknown(message_type(), bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t data_size() const {
        const auto bytes = data_bytes();
        switch (message_type()) {
            case MessageType::SystemTimeMessage: return SystemTimeMessage{ bytes }.encoded_size();
            case MessageType::SimpleSeriesUpdateMessage: return SimpleSeriesUpdateMessage{ bytes }.encoded_size();
            case MessageType::SystemStateMessage: return SystemStateMessage{ bytes }.encoded_size();
            case MessageType::SimpleTopOfMarketBestBidOrOfferCompactBidMessage: return SimpleTopOfMarketBestBidOrOfferCompactBidMessage{ bytes }.encoded_size();
            case MessageType::SimpleTopOfMarketBestBidOrOfferCompactOfferMessage: return SimpleTopOfMarketBestBidOrOfferCompactOfferMessage{ bytes }.encoded_size();
            case MessageType::SimpleTopOfMarketBestBidOrOfferWideBidMessage: return SimpleTopOfMarketBestBidOrOfferWideBidMessage{ bytes }.encoded_size();
            case MessageType::SimpleTopOfMarketBestBidOrOfferWideOfferMessage: return SimpleTopOfMarketBestBidOrOfferWideOfferMessage{ bytes }.encoded_size();
            case MessageType::SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage: return SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage{ bytes }.encoded_size();
            case MessageType::SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage: return SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage{ bytes }.encoded_size();
            case MessageType::LastSaleMessage: return LastSaleMessage{ bytes }.encoded_size();
            case MessageType::TradeCancelMessage: return TradeCancelMessage{ bytes }.encoded_size();
            case MessageType::UnderlyingTradingStatusNotificationMessage: return UnderlyingTradingStatusNotificationMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void data_print(std::ostream& out) const {
        const auto bytes = data_bytes();
        switch (message_type()) {
            case MessageType::SystemTimeMessage: SystemTimeMessage{ bytes }.print(out); return;
            case MessageType::SimpleSeriesUpdateMessage: SimpleSeriesUpdateMessage{ bytes }.print(out); return;
            case MessageType::SystemStateMessage: SystemStateMessage{ bytes }.print(out); return;
            case MessageType::SimpleTopOfMarketBestBidOrOfferCompactBidMessage: SimpleTopOfMarketBestBidOrOfferCompactBidMessage{ bytes }.print(out); return;
            case MessageType::SimpleTopOfMarketBestBidOrOfferCompactOfferMessage: SimpleTopOfMarketBestBidOrOfferCompactOfferMessage{ bytes }.print(out); return;
            case MessageType::SimpleTopOfMarketBestBidOrOfferWideBidMessage: SimpleTopOfMarketBestBidOrOfferWideBidMessage{ bytes }.print(out); return;
            case MessageType::SimpleTopOfMarketBestBidOrOfferWideOfferMessage: SimpleTopOfMarketBestBidOrOfferWideOfferMessage{ bytes }.print(out); return;
            case MessageType::SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage: SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage{ bytes }.print(out); return;
            case MessageType::SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage: SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage{ bytes }.print(out); return;
            case MessageType::LastSaleMessage: LastSaleMessage{ bytes }.print(out); return;
            case MessageType::TradeCancelMessage: TradeCancelMessage{ bytes }.print(out); return;
            case MessageType::UnderlyingTradingStatusNotificationMessage: UnderlyingTradingStatusNotificationMessage{ bytes }.print(out); return;
            default:
                out << "UnknownData{type=" << message_type() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "RefreshResponseMessageApplicationMessage{";
        out << "message_type=";
        out << message_type();
        out << ", data=";
        data_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t data_end() const { return 1 + data_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RefreshResponseMessageApplicationMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
