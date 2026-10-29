#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

class Visitor;

// Order Executed messages are sent when a visible order on the Cboe book is executed in whole
// or in part
class OrderExecutedMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderExecutedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 24;

    OrderExecutedMessage() = default;
    OrderExecutedMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, std::uint32_t executed_quantity, std::uint64_t execution_id);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Order Id: Day-specific identifier assigned to this order
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Executed Quantity: Number of shares/contracts executed
    std::uint32_t executed_quantity() const;
    void set_executed_quantity(std::uint32_t value);

    // Execution Id: Cboe generated day-unique execution identifier of this execution.
    // Execution Id is also referenced in the Trade Break message
    std::uint64_t execution_id() const;
    void set_execution_id(std::uint64_t value);

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

    bool operator==(const OrderExecutedMessage& other) const;
    bool operator!=(const OrderExecutedMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::uint64_t order_id_{};
    std::uint32_t executed_quantity_{};
    std::uint64_t execution_id_{};
};

} // namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29
