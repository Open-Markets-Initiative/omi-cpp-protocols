#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../enums/QuoteCondition.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

class Visitor;

// The options system uses this administrative message to indicate when an strategy has
// completed the opening process and is now available for auto execution or when the option has
// closed and is no longer available for auto execution.
class StrategyBestBidAndAskUpdate : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::StrategyBestBidAndAskUpdate;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 67;

    StrategyBestBidAndAskUpdate() = default;
    StrategyBestBidAndAskUpdate(std::chrono::nanoseconds timestamp, std::uint32_t strategy_id, QuoteCondition quote_condition, Decimal bid_price, std::uint32_t bid_size, std::uint32_t bid_cust_size, std::uint32_t bid_pro_cust_size, std::uint32_t bid_ntt_size, std::uint32_t bid_market_size, std::uint32_t bid_ntt_market_size, Decimal ask_price, std::uint32_t ask_size, std::uint32_t ask_cust_size, std::uint32_t ask_pro_cust_size, std::uint32_t ask_ntt_size, std::uint32_t ask_market_size, std::uint32_t ask_ntt_market_size);

    // Timestamp: The time, expressed as the number of nanoseconds after midnight.
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Strategy Id: ISE’s Strategy ID assigned daily, valid while there are any open complex
    // orders for the day
    std::uint32_t strategy_id() const;
    void set_strategy_id(std::uint32_t value);

    // Quote Condition: <space> = regular quote/autox eligible “X” = Pre-Open/Halted
    QuoteCondition quote_condition() const;
    void set_quote_condition(QuoteCondition value);

    // Bid Price: Best bid price in fixed point format with 6 whole number places followed by 4
    // decimal digits.
    Decimal bid_price() const;
    void set_bid_price(Decimal value);

    // Bid Size: Aggregated number of contracts on the bid side being displayed in the options
    // market at the current time.
    std::uint32_t bid_size() const;
    void set_bid_size(std::uint32_t value);

    // Bid Cust Size: Customer quantity on the bid side.
    std::uint32_t bid_cust_size() const;
    void set_bid_cust_size(std::uint32_t value);

    // Bid Pro Cust Size: Customer professional quantity on the bid side.
    std::uint32_t bid_pro_cust_size() const;
    void set_bid_pro_cust_size(std::uint32_t value);

    // Bid Ntt Size: Limit Bid size that can’t be traded through.
    std::uint32_t bid_ntt_size() const;
    void set_bid_ntt_size(std::uint32_t value);

    // Bid Market Size: The aggregate market size on Bid side.
    std::uint32_t bid_market_size() const;
    void set_bid_market_size(std::uint32_t value);

    // Bid Ntt Market Size: The aggregated NTT Market Size on Bid Size.
    std::uint32_t bid_ntt_market_size() const;
    void set_bid_ntt_market_size(std::uint32_t value);

    // Ask Price: Best ask price in fixed point format with 6 whole number places followed by 4
    // decimal digits.
    Decimal ask_price() const;
    void set_ask_price(Decimal value);

    // Ask Size: Aggregated number of contracts on the ask side being displayed in the options
    // market at the current time.
    std::uint32_t ask_size() const;
    void set_ask_size(std::uint32_t value);

    // Ask Cust Size: Customer quantity on the ask side.
    std::uint32_t ask_cust_size() const;
    void set_ask_cust_size(std::uint32_t value);

    // Ask Pro Cust Size: Customer professional quantity on the ask side.
    std::uint32_t ask_pro_cust_size() const;
    void set_ask_pro_cust_size(std::uint32_t value);

    // Ask Ntt Size: Limit Ask size that can’t be traded through.
    std::uint32_t ask_ntt_size() const;
    void set_ask_ntt_size(std::uint32_t value);

    // Ask Market Size: Aggregate market quantity on Ask side.
    std::uint32_t ask_market_size() const;
    void set_ask_market_size(std::uint32_t value);

    // Ask Ntt Market Size: The aggregated NTT Market Size on Ask Size.
    std::uint32_t ask_ntt_market_size() const;
    void set_ask_ntt_market_size(std::uint32_t value);

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

    bool operator==(const StrategyBestBidAndAskUpdate& other) const;
    bool operator!=(const StrategyBestBidAndAskUpdate& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t strategy_id_{};
    QuoteCondition quote_condition_{};
    Decimal bid_price_{ 0, -4 };
    std::uint32_t bid_size_{};
    std::uint32_t bid_cust_size_{};
    std::uint32_t bid_pro_cust_size_{};
    std::uint32_t bid_ntt_size_{};
    std::uint32_t bid_market_size_{};
    std::uint32_t bid_ntt_market_size_{};
    Decimal ask_price_{ 0, -4 };
    std::uint32_t ask_size_{};
    std::uint32_t ask_cust_size_{};
    std::uint32_t ask_pro_cust_size_{};
    std::uint32_t ask_ntt_size_{};
    std::uint32_t ask_market_size_{};
    std::uint32_t ask_ntt_market_size_{};
};

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
