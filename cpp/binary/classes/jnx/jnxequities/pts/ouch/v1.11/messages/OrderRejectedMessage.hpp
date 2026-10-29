#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../enums/OrderRejectedReason.hpp"
#include "../messages/SequencedMessage.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

class SequencedMessageVisitor;

// An Order Rejected Message may be sent in response to an Enter Order Message if the order
// cannot be accepted
class OrderRejectedMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::OrderRejectedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 13;

    OrderRejectedMessage() = default;
    OrderRejectedMessage(std::chrono::nanoseconds timestamp, std::uint32_t order_token, OrderRejectedReason order_rejected_reason);

    // Timestamp: Number of nanoseconds past midnight of the current calendar date
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Order Token: Must be unique per Ouch account within a trading day and increase on each
    // subsequent transaction
    std::uint32_t order_token() const;
    void set_order_token(std::uint32_t value);

    // Order Rejected Reason: Reason the order was rejected
    OrderRejectedReason order_rejected_reason() const;
    void set_order_rejected_reason(OrderRejectedReason value);

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

    bool operator==(const OrderRejectedMessage& other) const;
    bool operator!=(const OrderRejectedMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t order_token_{};
    OrderRejectedReason order_rejected_reason_{};
};

} // namespace jnx::jnxequities::pts::ouch::v1_11
