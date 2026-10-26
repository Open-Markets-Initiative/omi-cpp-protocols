#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/TradeCondition.hpp"
#include "../messages/Message.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

class Visitor;

// Order Executed at Price/Size messages are sent when a visible order on the Cboe book is
// executed in whole or in part at a different price than the limit price on the original Add
// Order message or the limit order price in the latest Modify Order message referencing the
// Order Id. If the Remaining Quantity field contains a 0 the order should be completely
// removed from the book. Order Executed at Price/Size messages may also be sent in cases where
// the Executed Quantity is greater than the current booked size for Order Id due to Exchange
// features that allow a portion of an order to be hidden while another portion is displayed.
class OrderExecutedAtPriceSizeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderExecutedAtPriceSizeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 37;

    OrderExecutedAtPriceSizeMessage() = default;
    OrderExecutedAtPriceSizeMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, std::uint32_t executed_quantity, std::uint32_t remaining_quantity, std::uint64_t execution_id, Decimal price_long, TradeCondition trade_condition);

    // Time Offset: Nanosecond offset from last unit timestamp.
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Order Id: Day-specific identifier assigned to this order.
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Executed Quantity: Number of shares/contracts executed.
    std::uint32_t executed_quantity() const;
    void set_executed_quantity(std::uint32_t value);

    // Remaining Quantity: Number of shares/contracts remaining after the execution.
    std::uint32_t remaining_quantity() const;
    void set_remaining_quantity(std::uint32_t value);

    // Execution Id: Cboe generated day-unique execution identifier of this execution.
    // Execution Id is also referenced in the Trade Break message.
    std::uint64_t execution_id() const;
    void set_execution_id(std::uint64_t value);

    // Price Long: The limit order price.
    Decimal price_long() const;
    void set_price_long(Decimal value);

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

    bool operator==(const OrderExecutedAtPriceSizeMessage& other) const;
    bool operator!=(const OrderExecutedAtPriceSizeMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::uint64_t order_id_{};
    std::uint32_t executed_quantity_{};
    std::uint32_t remaining_quantity_{};
    std::uint64_t execution_id_{};
    Decimal price_long_{ 0, -4 };
    TradeCondition trade_condition_{};
};

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
