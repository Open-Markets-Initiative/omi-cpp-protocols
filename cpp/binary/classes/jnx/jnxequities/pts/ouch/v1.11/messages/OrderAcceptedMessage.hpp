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
#include "../enums/Capacity.hpp"
#include "../enums/CashMarginType.hpp"
#include "../enums/Display.hpp"
#include "../enums/Group.hpp"
#include "../enums/OrderClassification.hpp"
#include "../enums/OrderState.hpp"
#include "../enums/TimeInForce.hpp"
#include "../messages/SequencedMessage.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

class SequencedMessageVisitor;

// An Order Accepted Message acknowledges the receipt and acceptance of a valid Enter Order
// Message
class OrderAcceptedMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::OrderAcceptedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 64;

    OrderAcceptedMessage() = default;
    OrderAcceptedMessage(std::chrono::nanoseconds timestamp, std::uint32_t order_token, const std::string& client_reference, BuySellIndicator buy_sell_indicator, std::uint32_t quantity, std::uint32_t orderbook_id, const std::string& group, Decimal price, TimeInForce time_in_force, std::uint32_t firm_id, Display display, Capacity capacity, std::uint64_t order_number, std::uint32_t minimum_quantity, OrderState order_state, OrderClassification order_classification, CashMarginType cash_margin_type);

    // Timestamp: Number of nanoseconds past midnight of the current calendar date
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Order Token: Must be unique per Ouch account within a trading day and increase on each
    // subsequent transaction
    std::uint32_t order_token() const;
    void set_order_token(std::uint32_t value);

    // Client Reference: Assigned by client Not validated
    const std::string& client_reference() const;
    std::string& client_reference();
    void set_client_reference(const std::string& value);

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

    // Firm Id: Order entry firm identifier
    std::uint32_t firm_id() const;
    void set_firm_id(std::uint32_t value);

    // Display: Order handling instruction
    Display display() const;
    void set_display(Display value);

    // Capacity: Capacity of firm placing order
    Capacity capacity() const;
    void set_capacity(Capacity value);

    // Order Number: Order reference number unique within trading day
    std::uint64_t order_number() const;
    void set_order_number(std::uint64_t value);

    // Minimum Quantity: Minimum acceptable quantity to execute
    std::uint32_t minimum_quantity() const;
    void set_minimum_quantity(std::uint32_t value);

    // Order State: Order state upon acceptance
    OrderState order_state() const;
    void set_order_state(OrderState value);

    // Order Classification: High-frequency trading order classification
    OrderClassification order_classification() const;
    void set_order_classification(OrderClassification value);

    // Cash Margin Type: Cash margin type of order
    CashMarginType cash_margin_type() const;
    void set_cash_margin_type(CashMarginType value);

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

    bool operator==(const OrderAcceptedMessage& other) const;
    bool operator!=(const OrderAcceptedMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t order_token_{};
    std::string client_reference_{};
    BuySellIndicator buy_sell_indicator_{};
    std::uint32_t quantity_{};
    std::uint32_t orderbook_id_{};
    std::string group_{};
    Decimal price_{ 0, -1 };
    TimeInForce time_in_force_{};
    std::uint32_t firm_id_{};
    Display display_{};
    Capacity capacity_{};
    std::uint64_t order_number_{};
    std::uint32_t minimum_quantity_{};
    OrderState order_state_{};
    OrderClassification order_classification_{};
    CashMarginType cash_margin_type_{};
};

} // namespace jnx::jnxequities::pts::ouch::v1_11
