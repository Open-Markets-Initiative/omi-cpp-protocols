#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../enums/LiquidityIndicator.hpp"
#include "../messages/SequencedMessage.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

class SequencedMessageVisitor;

// An Order Executed Message denotes that all or part of an order has been executed
class OrderExecutedMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::OrderExecutedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 29;

    OrderExecutedMessage() = default;
    OrderExecutedMessage(std::chrono::nanoseconds timestamp, std::uint32_t order_token, std::uint32_t executed_quantity, Decimal execution_price, LiquidityIndicator liquidity_indicator, std::uint64_t match_number);

    // Timestamp: Number of nanoseconds past midnight of the current calendar date
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Order Token: Must be unique per Ouch account within a trading day and increase on each
    // subsequent transaction
    std::uint32_t order_token() const;
    void set_order_token(std::uint32_t value);

    // Executed Quantity: Incremental number of shares executed
    std::uint32_t executed_quantity() const;
    void set_executed_quantity(std::uint32_t value);

    // Execution Price: Price at which the trade would have occurred
    Decimal execution_price() const;
    void set_execution_price(Decimal value);

    // Liquidity Indicator: Identifies whether this would-be trade was a result of a liquidity
    // provider providing or liquidity taker taking the liquidity
    LiquidityIndicator liquidity_indicator() const;
    void set_liquidity_indicator(LiquidityIndicator value);

    // Match Number: Reference number of the match unique within trading day
    std::uint64_t match_number() const;
    void set_match_number(std::uint64_t value);

    // SequencedMessage
    SequencedMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(SequencedMessageVisitor& visitor) const override;
    std::unique_ptr<SequencedMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const SequencedMessage& other) const override;

    bool operator==(const OrderExecutedMessage& other) const;
    bool operator!=(const OrderExecutedMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t order_token_{};
    std::uint32_t executed_quantity_{};
    Decimal execution_price_{ 0, -1 };
    LiquidityIndicator liquidity_indicator_{};
    std::uint64_t match_number_{};
};

} // namespace jnx::jnxequities::pts::ouch::v1_11
