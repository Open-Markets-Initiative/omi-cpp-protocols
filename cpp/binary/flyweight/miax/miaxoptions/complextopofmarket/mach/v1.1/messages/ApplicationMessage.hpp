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
#include "../messages/SeriesUpdate.hpp"
#include "../messages/ComplexStrategyDefinitionMessage.hpp"
#include "../messages/SystemStateMessage.hpp"
#include "../messages/CompactComplexTopOfMarketBidMessage.hpp"
#include "../messages/CompactComplexTopOfMarketOfferMessage.hpp"
#include "../messages/WideComplexTopOfMarketBidMessage.hpp"
#include "../messages/WideComplexTopOfMarketOfferMessage.hpp"
#include "../messages/CompactComplexDoubleSidedTopOfMarketMessage.hpp"
#include "../messages/WideComplexDoubleSidedTopOfMarketMessage.hpp"
#include "../messages/StrategyTradeMessage.hpp"
#include "../messages/UnderlyingTradingStatusMessage.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

class ApplicationMessage {
  public:
    static constexpr const char* name = "ApplicationMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ApplicationMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ApplicationMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return data_end(); }

    MessageType message_type() const { return static_cast<MessageType>(wire::read_char(at(0))); }

    // the bytes the message it selects is read from
    std::span<const std::byte> data_bytes() const {
        wire::require("ApplicationMessage", 1, bytes_.size());
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
            case MessageType::SeriesUpdate: {
                wire::require(SeriesUpdate::name, SeriesUpdate::minimum_size, bytes.size());
                const SeriesUpdate message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::ComplexStrategyDefinitionMessage: {
                wire::require(ComplexStrategyDefinitionMessage::name, ComplexStrategyDefinitionMessage::minimum_size, bytes.size());
                const ComplexStrategyDefinitionMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::SystemStateMessage: {
                wire::require(SystemStateMessage::name, SystemStateMessage::minimum_size, bytes.size());
                const SystemStateMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::CompactComplexTopOfMarketBidMessage: {
                wire::require(CompactComplexTopOfMarketBidMessage::name, CompactComplexTopOfMarketBidMessage::minimum_size, bytes.size());
                const CompactComplexTopOfMarketBidMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::CompactComplexTopOfMarketOfferMessage: {
                wire::require(CompactComplexTopOfMarketOfferMessage::name, CompactComplexTopOfMarketOfferMessage::minimum_size, bytes.size());
                const CompactComplexTopOfMarketOfferMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::WideComplexTopOfMarketBidMessage: {
                wire::require(WideComplexTopOfMarketBidMessage::name, WideComplexTopOfMarketBidMessage::minimum_size, bytes.size());
                const WideComplexTopOfMarketBidMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::WideComplexTopOfMarketOfferMessage: {
                wire::require(WideComplexTopOfMarketOfferMessage::name, WideComplexTopOfMarketOfferMessage::minimum_size, bytes.size());
                const WideComplexTopOfMarketOfferMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::CompactComplexDoubleSidedTopOfMarketMessage: {
                wire::require(CompactComplexDoubleSidedTopOfMarketMessage::name, CompactComplexDoubleSidedTopOfMarketMessage::minimum_size, bytes.size());
                const CompactComplexDoubleSidedTopOfMarketMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::WideComplexDoubleSidedTopOfMarketMessage: {
                wire::require(WideComplexDoubleSidedTopOfMarketMessage::name, WideComplexDoubleSidedTopOfMarketMessage::minimum_size, bytes.size());
                const WideComplexDoubleSidedTopOfMarketMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::StrategyTradeMessage: {
                wire::require(StrategyTradeMessage::name, StrategyTradeMessage::minimum_size, bytes.size());
                const StrategyTradeMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MessageType::UnderlyingTradingStatusMessage: {
                wire::require(UnderlyingTradingStatusMessage::name, UnderlyingTradingStatusMessage::minimum_size, bytes.size());
                const UnderlyingTradingStatusMessage message{ bytes };
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
            case MessageType::SeriesUpdate: return SeriesUpdate{ bytes }.encoded_size();
            case MessageType::ComplexStrategyDefinitionMessage: return ComplexStrategyDefinitionMessage{ bytes }.encoded_size();
            case MessageType::SystemStateMessage: return SystemStateMessage{ bytes }.encoded_size();
            case MessageType::CompactComplexTopOfMarketBidMessage: return CompactComplexTopOfMarketBidMessage{ bytes }.encoded_size();
            case MessageType::CompactComplexTopOfMarketOfferMessage: return CompactComplexTopOfMarketOfferMessage{ bytes }.encoded_size();
            case MessageType::WideComplexTopOfMarketBidMessage: return WideComplexTopOfMarketBidMessage{ bytes }.encoded_size();
            case MessageType::WideComplexTopOfMarketOfferMessage: return WideComplexTopOfMarketOfferMessage{ bytes }.encoded_size();
            case MessageType::CompactComplexDoubleSidedTopOfMarketMessage: return CompactComplexDoubleSidedTopOfMarketMessage{ bytes }.encoded_size();
            case MessageType::WideComplexDoubleSidedTopOfMarketMessage: return WideComplexDoubleSidedTopOfMarketMessage{ bytes }.encoded_size();
            case MessageType::StrategyTradeMessage: return StrategyTradeMessage{ bytes }.encoded_size();
            case MessageType::UnderlyingTradingStatusMessage: return UnderlyingTradingStatusMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void data_print(std::ostream& out) const {
        const auto bytes = data_bytes();
        switch (message_type()) {
            case MessageType::SystemTimeMessage: SystemTimeMessage{ bytes }.print(out); return;
            case MessageType::SeriesUpdate: SeriesUpdate{ bytes }.print(out); return;
            case MessageType::ComplexStrategyDefinitionMessage: ComplexStrategyDefinitionMessage{ bytes }.print(out); return;
            case MessageType::SystemStateMessage: SystemStateMessage{ bytes }.print(out); return;
            case MessageType::CompactComplexTopOfMarketBidMessage: CompactComplexTopOfMarketBidMessage{ bytes }.print(out); return;
            case MessageType::CompactComplexTopOfMarketOfferMessage: CompactComplexTopOfMarketOfferMessage{ bytes }.print(out); return;
            case MessageType::WideComplexTopOfMarketBidMessage: WideComplexTopOfMarketBidMessage{ bytes }.print(out); return;
            case MessageType::WideComplexTopOfMarketOfferMessage: WideComplexTopOfMarketOfferMessage{ bytes }.print(out); return;
            case MessageType::CompactComplexDoubleSidedTopOfMarketMessage: CompactComplexDoubleSidedTopOfMarketMessage{ bytes }.print(out); return;
            case MessageType::WideComplexDoubleSidedTopOfMarketMessage: WideComplexDoubleSidedTopOfMarketMessage{ bytes }.print(out); return;
            case MessageType::StrategyTradeMessage: StrategyTradeMessage{ bytes }.print(out); return;
            case MessageType::UnderlyingTradingStatusMessage: UnderlyingTradingStatusMessage{ bytes }.print(out); return;
            default:
                out << "UnknownData{type=" << message_type() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "ApplicationMessage{";
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

inline std::ostream& operator<<(std::ostream& out, const ApplicationMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
