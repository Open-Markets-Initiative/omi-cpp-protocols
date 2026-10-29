#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../enums/BuySellIndicator.hpp"
#include "../enums/Display.hpp"
#include "../enums/Group.hpp"
#include "../enums/OrderState.hpp"
#include "../enums/TimeInForce.hpp"
#include "../messages/SequencedMessage.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

class SequencedMessageVisitor;

// An Order Replaced Message acknowledges the receipt and acceptance of a valid Replace Order
// Message
class OrderReplacedMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::OrderReplacedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 51;

    OrderReplacedMessage() = default;
    OrderReplacedMessage(std::chrono::nanoseconds timestamp, std::uint32_t replacement_order_token, BuySellIndicator buy_sell_indicator, std::uint32_t quantity, std::uint32_t orderbook_id, const std::string& group, Decimal price, TimeInForce time_in_force, Display display, std::uint64_t order_number, std::uint32_t minimum_quantity, OrderState order_state, std::uint32_t previous_order_token);

    // Timestamp: Number of nanoseconds past midnight of the current calendar date
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Replacement Order Token: Must be unique per Ouch account within a trading day and
    // increase on each subsequent transaction
    std::uint32_t replacement_order_token() const;
    void set_replacement_order_token(std::uint32_t value);

    // Buy Sell Indicator: Side of order
    BuySellIndicator buy_sell_indicator() const;
    void set_buy_sell_indicator(BuySellIndicator value);

    // Quantity: Number of shares
    std::uint32_t quantity() const;
    void set_quantity(std::uint32_t value);

    // Orderbook Id: 4 digit Quick code
    std::uint32_t orderbook_id() const;
    void set_orderbook_id(std::uint32_t value);

    // Group: Order book group identifier
    const std::string& group() const;
    std::string& group();
    void set_group(const std::string& value);

    // Price: Order price
    Decimal price() const;
    void set_price(Decimal value);

    // Time In Force: How long the order remains in effect
    TimeInForce time_in_force() const;
    void set_time_in_force(TimeInForce value);

    // Display: Order handling instruction
    Display display() const;
    void set_display(Display value);

    // Order Number: Order reference number unique within trading day
    std::uint64_t order_number() const;
    void set_order_number(std::uint64_t value);

    // Minimum Quantity: Minimum acceptable quantity to execute
    std::uint32_t minimum_quantity() const;
    void set_minimum_quantity(std::uint32_t value);

    // Order State: Order state upon acceptance
    OrderState order_state() const;
    void set_order_state(OrderState value);

    // Previous Order Token: Order token of replaced order
    std::uint32_t previous_order_token() const;
    void set_previous_order_token(std::uint32_t value);

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

    bool operator==(const OrderReplacedMessage& other) const;
    bool operator!=(const OrderReplacedMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t replacement_order_token_{};
    BuySellIndicator buy_sell_indicator_{};
    std::uint32_t quantity_{};
    std::uint32_t orderbook_id_{};
    std::string group_{};
    Decimal price_{ 0, -1 };
    TimeInForce time_in_force_{};
    Display display_{};
    std::uint64_t order_number_{};
    std::uint32_t minimum_quantity_{};
    OrderState order_state_{};
    std::uint32_t previous_order_token_{};
};

} // namespace jnx::jnxequities::pts::ouch::v1_11
