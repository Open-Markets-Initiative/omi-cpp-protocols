#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

class Visitor;

// The Delete Order message is sent whenever a booked order is cancelled or leaves the order
// book. The Order Id refers to the Order Id of the original Add Order message. An order that
// is deleted from the book may return to the book later under certain circumstances.
// Therefore, a Delete Order message does not indicate that a given Order Id will not be sent
// again on a subsequent Add Order message.
class DeleteOrderMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::DeleteOrderMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 12;

    DeleteOrderMessage() = default;
    DeleteOrderMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id);

    // Time Offset: Nanosecond offset from last unit timestamp.
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Order Id: Day-specific identifier assigned to this order.
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

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

    bool operator==(const DeleteOrderMessage& other) const;
    bool operator!=(const DeleteOrderMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::uint64_t order_id_{};
};

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
