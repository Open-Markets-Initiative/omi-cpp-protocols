#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../bitfields/MatchEventIndicator.hpp"
#include "../common/Decimal.hpp"
#include "../enums/TradingSessionId.hpp"
#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

class Visitor;

// TradeBust_57Message
class TradeBust57Message : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::TradeBust57Message;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 48;

    TradeBust57Message() = default;
    TradeBust57Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, TradingSessionId trading_session_id, const std::array<std::byte, 2>& offset_10_padding_2, Decimal md_future_price, std::int64_t md_entry_size_quantity, std::uint32_t trade_id, std::uint16_t trade_date, const std::array<std::byte, 2>& offset_34_padding_2, std::optional<std::chrono::nanoseconds> md_entry_timestamp, std::optional<std::uint32_t> rpt_seq);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Match Event Indicator: MatchEventIndicator bit set
    const MatchEventIndicator& match_event_indicator() const;
    MatchEventIndicator& match_event_indicator();
    void set_match_event_indicator(const MatchEventIndicator& value);

    // Trading Session Id: tradingSessionID
    TradingSessionId trading_session_id() const;
    void set_trading_session_id(TradingSessionId value);

    // Offset 10 Padding 2: 2 bytes padding
    const std::array<std::byte, 2>& offset_10_padding_2() const;
    std::array<std::byte, 2>& offset_10_padding_2();
    void set_offset_10_padding_2(const std::array<std::byte, 2>& value);

    // Md Future Price: mDEntryPx
    Decimal md_future_price() const;
    void set_md_future_price(Decimal value);

    // Md Entry Size Quantity: mDEntrySize
    std::int64_t md_entry_size_quantity() const;
    void set_md_entry_size_quantity(std::int64_t value);

    // Trade Id: tradeID
    std::uint32_t trade_id() const;
    void set_trade_id(std::uint32_t value);

    // Trade Date: tradeDate
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Offset 34 Padding 2: 2 bytes padding
    const std::array<std::byte, 2>& offset_34_padding_2() const;
    std::array<std::byte, 2>& offset_34_padding_2();
    void set_offset_34_padding_2(const std::array<std::byte, 2>& value);

    // Md Entry Timestamp: mDEntryTimestamp
    std::optional<std::chrono::nanoseconds> md_entry_timestamp() const;
    void set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value);

    // Rpt Seq: rptSeq
    std::optional<std::uint32_t> rpt_seq() const;
    void set_rpt_seq(std::optional<std::uint32_t> value);

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

    bool operator==(const TradeBust57Message& other) const;
    bool operator!=(const TradeBust57Message& other) const;

  private:
    std::uint64_t security_id_{};
    MatchEventIndicator match_event_indicator_{};
    TradingSessionId trading_session_id_{};
    std::array<std::byte, 2> offset_10_padding_2_{};
    Decimal md_future_price_{ 0, -4 };
    std::int64_t md_entry_size_quantity_{};
    std::uint32_t trade_id_{};
    std::uint16_t trade_date_{};
    std::array<std::byte, 2> offset_34_padding_2_{};
    std::optional<std::chrono::nanoseconds> md_entry_timestamp_{};
    std::optional<std::uint32_t> rpt_seq_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
