#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../bitfields/MatchEventIndicator.hpp"
#include "../bitfields/TradeCondition.hpp"
#include "../common/Decimal.hpp"
#include "../enums/TradingSessionId.hpp"
#include "../enums/TrdSubType.hpp"
#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

class Visitor;

// ForwardTrade_54Message
class ForwardTrade54Message : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::ForwardTrade54Message;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 68;

    ForwardTrade54Message() = default;
    ForwardTrade54Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, TradingSessionId trading_session_id, const TradeCondition& trade_condition, Decimal md_future_price, std::int64_t md_entry_size_quantity, std::uint32_t trade_id, std::optional<std::uint32_t> md_entry_buyer, std::optional<std::uint32_t> md_entry_seller, std::uint16_t trade_date, std::optional<std::uint64_t> transact_time, std::optional<std::uint32_t> rpt_seq, std::optional<std::uint16_t> seller_days, std::optional<Decimal> md_entry_interest_rate, std::optional<TrdSubType> trd_sub_type, const std::array<std::byte, 3>& padding_3);

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

    // Trade Condition: TradeCondition bit set
    const TradeCondition& trade_condition() const;
    TradeCondition& trade_condition();
    void set_trade_condition(const TradeCondition& value);

    // Md Future Price: mDEntryPx
    Decimal md_future_price() const;
    void set_md_future_price(Decimal value);

    // Md Entry Size Quantity: mDEntrySize
    std::int64_t md_entry_size_quantity() const;
    void set_md_entry_size_quantity(std::int64_t value);

    // Trade Id: tradeID
    std::uint32_t trade_id() const;
    void set_trade_id(std::uint32_t value);

    // Md Entry Buyer: mDEntryBuyer
    std::optional<std::uint32_t> md_entry_buyer() const;
    void set_md_entry_buyer(std::optional<std::uint32_t> value);

    // Md Entry Seller: mDEntrySeller
    std::optional<std::uint32_t> md_entry_seller() const;
    void set_md_entry_seller(std::optional<std::uint32_t> value);

    // Trade Date: tradeDate
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Transact Time: transactTime
    std::optional<std::uint64_t> transact_time() const;
    void set_transact_time(std::optional<std::uint64_t> value);

    // Rpt Seq: rptSeq
    std::optional<std::uint32_t> rpt_seq() const;
    void set_rpt_seq(std::optional<std::uint32_t> value);

    // Seller Days: sellerDays
    std::optional<std::uint16_t> seller_days() const;
    void set_seller_days(std::optional<std::uint16_t> value);

    // Md Entry Interest Rate: mDEntryInterestRate
    std::optional<Decimal> md_entry_interest_rate() const;
    void set_md_entry_interest_rate(std::optional<Decimal> value);

    // Trd Sub Type: trdSubType
    std::optional<TrdSubType> trd_sub_type() const;
    void set_trd_sub_type(std::optional<TrdSubType> value);

    // Padding 3: 3 bytes padding
    const std::array<std::byte, 3>& padding_3() const;
    std::array<std::byte, 3>& padding_3();
    void set_padding_3(const std::array<std::byte, 3>& value);

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

    bool operator==(const ForwardTrade54Message& other) const;
    bool operator!=(const ForwardTrade54Message& other) const;

  private:
    std::uint64_t security_id_{};
    MatchEventIndicator match_event_indicator_{};
    TradingSessionId trading_session_id_{};
    TradeCondition trade_condition_{};
    Decimal md_future_price_{ 0, -4 };
    std::int64_t md_entry_size_quantity_{};
    std::uint32_t trade_id_{};
    std::optional<std::uint32_t> md_entry_buyer_{};
    std::optional<std::uint32_t> md_entry_seller_{};
    std::uint16_t trade_date_{};
    std::optional<std::uint64_t> transact_time_{};
    std::optional<std::uint32_t> rpt_seq_{};
    std::optional<std::uint16_t> seller_days_{};
    std::optional<Decimal> md_entry_interest_rate_{};
    std::optional<TrdSubType> trd_sub_type_{};
    std::array<std::byte, 3> padding_3_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
