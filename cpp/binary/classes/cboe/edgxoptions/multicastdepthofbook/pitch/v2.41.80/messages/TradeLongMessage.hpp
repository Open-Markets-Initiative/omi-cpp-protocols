#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/SideIndicator.hpp"
#include "../enums/TradeCondition.hpp"
#include "../messages/Message.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

class Visitor;

// The Trade message provides information about executions of non-displayed orders on the Cboe
// book and routed executions to other trading centers. In options a Trade message can also be
// sent when an auction executes against a non-displayed order, such as a contra response.
// Trade messages are necessary to calculate Cboe execution-based data. Trade messages do not
// alter the book and can be ignored if messages are being used solely to build a book. The
// Order ID of a hidden order is obfuscated by default in the Trade message, but may be
// optionally disseminated for a member's own orders upon request.
class TradeLongMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradeLongMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 40;

    TradeLongMessage() = default;
    TradeLongMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, SideIndicator side_indicator, std::uint32_t quantity_long, const std::string& symbol, Decimal price_long, std::uint64_t execution_id, TradeCondition trade_condition);

    // Time Offset: Nanosecond offset from last unit timestamp.
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Order Id: Day-specific identifier assigned to this order.
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Side Indicator: B = Buy Order, S = Sell Order.
    SideIndicator side_indicator() const;
    void set_side_indicator(SideIndicator value);

    // Quantity Long: Number of shares/contracts being added to the book (may be less than the
    // number entered).
    std::uint32_t quantity_long() const;
    void set_quantity_long(std::uint32_t value);

    // Symbol: Symbol right padded with spaces.
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Price Long: The limit order price.
    Decimal price_long() const;
    void set_price_long(Decimal value);

    // Execution Id: Cboe generated day-unique execution identifier of this execution.
    // Execution Id is also referenced in the Trade Break message.
    std::uint64_t execution_id() const;
    void set_execution_id(std::uint64_t value);

    // Trade Condition: Options Only (byte not sent in Equities). See Options Trade Condition
    // Codes on page 180 section for details about new codes.
    TradeCondition trade_condition() const;
    void set_trade_condition(TradeCondition value);

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

    bool operator==(const TradeLongMessage& other) const;
    bool operator!=(const TradeLongMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::uint64_t order_id_{};
    SideIndicator side_indicator_{};
    std::uint32_t quantity_long_{};
    std::string symbol_{};
    Decimal price_long_{ 0, -4 };
    std::uint64_t execution_id_{};
    TradeCondition trade_condition_{};
};

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
