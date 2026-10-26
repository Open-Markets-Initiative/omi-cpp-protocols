#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MarketStatusMessageType.hpp"
#include "../messages/MarketWideCircuitBreakerDeclineLevelStatusMessage.hpp"
#include "../messages/MarketWideCircuitBreakerStatusMessage.hpp"
#include "../messages/ApproximateAdjustedVolumeMarketCenterMessage.hpp"
#include "../messages/FractionalApproximateAdjustedVolumeMarketCenterMessage.hpp"
#include "../messages/ApproximateTradesAndTotalDollarValueMessage.hpp"
#include "../messages/CrossingSessionSummaryMessage.hpp"

namespace siac::cts::output::cta::v2_11_b {

// Market Status Category Market Status Messages Are Used To Provide Market Data Information
class MarketStatusMessage {
  public:
    static constexpr const char* name = "MarketStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MarketStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MarketStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 1;
    std::size_t encoded_size() const { return market_status_message_payload_end(); }

    MarketStatusMessageType market_status_message_type() const { return static_cast<MarketStatusMessageType>(wire::read_char(at(0))); }

    // the bytes the message it selects is read from
    std::span<const std::byte> market_status_message_payload_bytes() const {
        wire::require("MarketStatusMessage", 1, bytes_.size());
        return bytes_.subspan(1);
    }

    // the message its market_status_message_type selects, handed to the handler as its view
    template <typename Handler>
    void market_status_message_payload(Handler& handler) const {
        const auto bytes = market_status_message_payload_bytes();
        switch (market_status_message_type()) {
            case MarketStatusMessageType::MarketWideCircuitBreakerDeclineLevelStatus: {
                wire::require(MarketWideCircuitBreakerDeclineLevelStatusMessage::name, MarketWideCircuitBreakerDeclineLevelStatusMessage::minimum_size, bytes.size());
                const MarketWideCircuitBreakerDeclineLevelStatusMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MarketStatusMessageType::MarketWideCircuitBreakerStatus: {
                wire::require(MarketWideCircuitBreakerStatusMessage::name, MarketWideCircuitBreakerStatusMessage::minimum_size, bytes.size());
                const MarketWideCircuitBreakerStatusMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MarketStatusMessageType::ApproximateAdjustedVolumeMarketCenter: {
                wire::require(ApproximateAdjustedVolumeMarketCenterMessage::name, ApproximateAdjustedVolumeMarketCenterMessage::minimum_size, bytes.size());
                const ApproximateAdjustedVolumeMarketCenterMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MarketStatusMessageType::FractionalApproximateAdjustedVolumeMarketCenter: {
                wire::require(FractionalApproximateAdjustedVolumeMarketCenterMessage::name, FractionalApproximateAdjustedVolumeMarketCenterMessage::minimum_size, bytes.size());
                const FractionalApproximateAdjustedVolumeMarketCenterMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MarketStatusMessageType::ApproximateTradesAndTotalDollarValue: {
                wire::require(ApproximateTradesAndTotalDollarValueMessage::name, ApproximateTradesAndTotalDollarValueMessage::minimum_size, bytes.size());
                const ApproximateTradesAndTotalDollarValueMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            case MarketStatusMessageType::CrossingSessionSummary: {
                wire::require(CrossingSessionSummaryMessage::name, CrossingSessionSummaryMessage::minimum_size, bytes.size());
                const CrossingSessionSummaryMessage message{ bytes };
                if constexpr (requires { handler.on(message); }) { handler.on(message); }
                return;
            }
            default:
                if constexpr (requires { handler.on_unknown(market_status_message_type(), bytes); }) { handler.on_unknown(market_status_message_type(), bytes); }
                return;
        }
    }

    // the bytes the message it selects takes
    std::size_t market_status_message_payload_size() const {
        const auto bytes = market_status_message_payload_bytes();
        switch (market_status_message_type()) {
            case MarketStatusMessageType::MarketWideCircuitBreakerDeclineLevelStatus: return MarketWideCircuitBreakerDeclineLevelStatusMessage{ bytes }.encoded_size();
            case MarketStatusMessageType::MarketWideCircuitBreakerStatus: return MarketWideCircuitBreakerStatusMessage{ bytes }.encoded_size();
            case MarketStatusMessageType::ApproximateAdjustedVolumeMarketCenter: return ApproximateAdjustedVolumeMarketCenterMessage{ bytes }.encoded_size();
            case MarketStatusMessageType::FractionalApproximateAdjustedVolumeMarketCenter: return FractionalApproximateAdjustedVolumeMarketCenterMessage{ bytes }.encoded_size();
            case MarketStatusMessageType::ApproximateTradesAndTotalDollarValue: return ApproximateTradesAndTotalDollarValueMessage{ bytes }.encoded_size();
            case MarketStatusMessageType::CrossingSessionSummary: return CrossingSessionSummaryMessage{ bytes }.encoded_size();
            default: return bytes.size();
        }
    }

    // the message it selects, printed; a code no message answers to prints its bytes
    void market_status_message_payload_print(std::ostream& out) const {
        const auto bytes = market_status_message_payload_bytes();
        switch (market_status_message_type()) {
            case MarketStatusMessageType::MarketWideCircuitBreakerDeclineLevelStatus: MarketWideCircuitBreakerDeclineLevelStatusMessage{ bytes }.print(out); return;
            case MarketStatusMessageType::MarketWideCircuitBreakerStatus: MarketWideCircuitBreakerStatusMessage{ bytes }.print(out); return;
            case MarketStatusMessageType::ApproximateAdjustedVolumeMarketCenter: ApproximateAdjustedVolumeMarketCenterMessage{ bytes }.print(out); return;
            case MarketStatusMessageType::FractionalApproximateAdjustedVolumeMarketCenter: FractionalApproximateAdjustedVolumeMarketCenterMessage{ bytes }.print(out); return;
            case MarketStatusMessageType::ApproximateTradesAndTotalDollarValue: ApproximateTradesAndTotalDollarValueMessage{ bytes }.print(out); return;
            case MarketStatusMessageType::CrossingSessionSummary: CrossingSessionSummaryMessage{ bytes }.print(out); return;
            default:
                out << "UnknownMarketStatusMessagePayload{type=" << market_status_message_type() << ", body=";
                print::hex(out, bytes.data(), bytes.size());
                out << '}';
                return;
        }
    }

    void print(std::ostream& out) const {
        out << "MarketStatusMessage{";
        out << "market_status_message_type=";
        out << market_status_message_type();
        out << ", market_status_message_payload=";
        market_status_message_payload_print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t market_status_message_payload_end() const { return 1 + market_status_message_payload_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MarketStatusMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_11_b
