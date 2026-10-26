#pragma once

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

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

class Visitor;

// ExecutionStatistics_56Message
class ExecutionStatistics56Message : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::ExecutionStatistics56Message;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 52;

    ExecutionStatistics56Message() = default;
    ExecutionStatistics56Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, TradingSessionId trading_session_id, std::uint16_t trade_date, std::int64_t trade_volume, std::optional<Decimal> vwap_px, std::optional<Decimal> net_chg_prev_day, std::uint32_t number_of_trades, std::optional<std::chrono::nanoseconds> md_entry_timestamp, std::optional<std::uint32_t> rpt_seq);

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

    // Trade Date: tradeDate
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Trade Volume: tradeVolume
    std::int64_t trade_volume() const;
    void set_trade_volume(std::int64_t value);

    // Vwap Px: vwapPx
    std::optional<Decimal> vwap_px() const;
    void set_vwap_px(std::optional<Decimal> value);

    // Net Chg Prev Day: netChgPrevDay
    std::optional<Decimal> net_chg_prev_day() const;
    void set_net_chg_prev_day(std::optional<Decimal> value);

    // Number Of Trades: numberOfTrades
    std::uint32_t number_of_trades() const;
    void set_number_of_trades(std::uint32_t value);

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

    bool operator==(const ExecutionStatistics56Message& other) const;
    bool operator!=(const ExecutionStatistics56Message& other) const;

  private:
    std::uint64_t security_id_{};
    MatchEventIndicator match_event_indicator_{};
    TradingSessionId trading_session_id_{};
    std::uint16_t trade_date_{};
    std::int64_t trade_volume_{};
    std::optional<Decimal> vwap_px_{};
    std::optional<Decimal> net_chg_prev_day_{};
    std::uint32_t number_of_trades_{};
    std::optional<std::chrono::nanoseconds> md_entry_timestamp_{};
    std::optional<std::uint32_t> rpt_seq_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
