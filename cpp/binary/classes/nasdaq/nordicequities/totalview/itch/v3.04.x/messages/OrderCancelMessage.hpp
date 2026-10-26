#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

class Visitor;

// An order on the book modified by a partial cancellation
class OrderCancelMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderCancelMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 22;

    OrderCancelMessage() = default;
    OrderCancelMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint64_t order_reference_number, std::uint32_t canceled_quantity);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Tracking Number: Nasdaq Nordic internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Order Reference Number: Unique reference number assigned to the new order
    std::uint64_t order_reference_number() const;
    void set_order_reference_number(std::uint64_t value);

    // Canceled Quantity: Number of shares removed from the display size
    std::uint32_t canceled_quantity() const;
    void set_canceled_quantity(std::uint32_t value);

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

    bool operator==(const OrderCancelMessage& other) const;
    bool operator!=(const OrderCancelMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint16_t tracking_number_{};
    std::uint64_t order_reference_number_{};
    std::uint32_t canceled_quantity_{};
};

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
