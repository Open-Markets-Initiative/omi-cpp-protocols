#pragma once

#include <cstddef>
#include <cstdint>
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

// Product Summary
class ProductSummary : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::ProductSummary;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 8;

    ProductSummary() = default;
    ProductSummary(std::optional<std::uint32_t> last_msg_seq_num_processed, std::optional<TradingSessionId> trading_session_id, std::optional<TradingSessionSubId> trading_session_sub_id, std::optional<TradSesStatus> trad_ses_status, std::optional<FastMarketIndicator> fast_market_indicator);

    // Last Msg Seq Num Processed:
    std::optional<std::uint32_t> last_msg_seq_num_processed() const;
    void set_last_msg_seq_num_processed(std::optional<std::uint32_t> value);

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

    bool operator==(const ProductSummary& other) const;
    bool operator!=(const ProductSummary& other) const;

  private:
    std::optional<std::uint32_t> last_msg_seq_num_processed_{};
    std::optional<TradingSessionId> trading_session_id_{};
    std::optional<TradingSessionSubId> trading_session_sub_id_{};
    std::optional<TradSesStatus> trad_ses_status_{};
    std::optional<FastMarketIndicator> fast_market_indicator_{};
};

} // namespace eurex::t7::eobi::fbe::v3_0
