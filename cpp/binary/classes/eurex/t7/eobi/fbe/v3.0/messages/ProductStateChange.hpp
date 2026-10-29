#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../enums/FastMarketIndicator.hpp"
#include "../enums/TradSesStatus.hpp"
#include "../enums/TradingSessionId.hpp"
#include "../enums/TradingSessionSubId.hpp"
#include "../messages/Message.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

class Visitor;

// Product State Change
class ProductStateChange : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::ProductStateChange;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    ProductStateChange() = default;
    ProductStateChange(std::optional<TradingSessionId> trading_session_id, std::optional<TradingSessionSubId> trading_session_sub_id, std::optional<TradSesStatus> trad_ses_status, std::optional<FastMarketIndicator> fast_market_indicator, const std::array<std::byte, 4>& pad4, std::optional<std::chrono::nanoseconds> transact_time);

    // Trading Session Id:
    std::optional<TradingSessionId> trading_session_id() const;
    void set_trading_session_id(std::optional<TradingSessionId> value);

    // Trading Session Sub Id:
    std::optional<TradingSessionSubId> trading_session_sub_id() const;
    void set_trading_session_sub_id(std::optional<TradingSessionSubId> value);

    // Trad Ses Status:
    std::optional<TradSesStatus> trad_ses_status() const;
    void set_trad_ses_status(std::optional<TradSesStatus> value);

    // Fast Market Indicator:
    std::optional<FastMarketIndicator> fast_market_indicator() const;
    void set_fast_market_indicator(std::optional<FastMarketIndicator> value);

    // Pad4:
    const std::array<std::byte, 4>& pad4() const;
    std::array<std::byte, 4>& pad4();
    void set_pad4(const std::array<std::byte, 4>& value);

    // Transact Time: Matching-engine transaction time in nanoseconds since Unix epoch
    std::optional<std::chrono::nanoseconds> transact_time() const;
    void set_transact_time(std::optional<std::chrono::nanoseconds> value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const ProductStateChange& other) const;
    bool operator!=(const ProductStateChange& other) const;

  private:
    std::optional<TradingSessionId> trading_session_id_{};
    std::optional<TradingSessionSubId> trading_session_sub_id_{};
    std::optional<TradSesStatus> trad_ses_status_{};
    std::optional<FastMarketIndicator> fast_market_indicator_{};
    std::array<std::byte, 4> pad4_{};
    std::optional<std::chrono::nanoseconds> transact_time_{};
};

} // namespace eurex::t7::eobi::fbe::v3_0
