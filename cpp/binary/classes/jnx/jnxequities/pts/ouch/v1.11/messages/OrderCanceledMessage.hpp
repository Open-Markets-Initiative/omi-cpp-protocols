#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../enums/OrderCanceledReason.hpp"
#include "../messages/SequencedMessage.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

class SequencedMessageVisitor;

// An Order Canceled Message denotes that an order has been canceled
class OrderCanceledMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::OrderCanceledMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    OrderCanceledMessage() = default;
    OrderCanceledMessage(std::chrono::nanoseconds timestamp, std::uint32_t order_token, std::uint32_t decrement_quantity, OrderCanceledReason order_canceled_reason);

    // Timestamp: Number of nanoseconds past midnight of the current calendar date
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Order Token: Must be unique per Ouch account within a trading day and increase on each
    // subsequent transaction
    std::uint32_t order_token() const;
    void set_order_token(std::uint32_t value);

    // Decrement Quantity: Number of shares decremented from order
    std::uint32_t decrement_quantity() const;
    void set_decrement_quantity(std::uint32_t value);

    // Order Canceled Reason: Reason order was reduced or canceled
    OrderCanceledReason order_canceled_reason() const;
    void set_order_canceled_reason(OrderCanceledReason value);

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

    bool operator==(const OrderCanceledMessage& other) const;
    bool operator!=(const OrderCanceledMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t order_token_{};
    std::uint32_t decrement_quantity_{};
    OrderCanceledReason order_canceled_reason_{};
};

} // namespace jnx::jnxequities::pts::ouch::v1_11
