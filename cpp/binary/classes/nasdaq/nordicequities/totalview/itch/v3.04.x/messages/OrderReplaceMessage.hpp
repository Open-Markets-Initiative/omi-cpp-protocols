#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

class Visitor;

// An order on the book has been cancel replaced
class OrderReplaceMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderReplaceMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 34;

    OrderReplaceMessage() = default;
    OrderReplaceMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint64_t original_order_reference_number, std::uint64_t new_order_reference_number, std::uint32_t quantity, Decimal price);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Tracking Number: Nasdaq Nordic internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Original Order Reference Number: Reference number of the order being replaced
    std::uint64_t original_order_reference_number() const;
    void set_original_order_reference_number(std::uint64_t value);

    // New Order Reference Number: New reference number for this order
    std::uint64_t new_order_reference_number() const;
    void set_new_order_reference_number(std::uint64_t value);

    // Quantity: Total number of shares in the order
    std::uint32_t quantity() const;
    void set_quantity(std::uint32_t value);

    // Price: Display price of the new order
    Decimal price() const;
    void set_price(Decimal value);

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

    bool operator==(const OrderReplaceMessage& other) const;
    bool operator!=(const OrderReplaceMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint16_t tracking_number_{};
    std::uint64_t original_order_reference_number_{};
    std::uint64_t new_order_reference_number_{};
    std::uint32_t quantity_{};
    Decimal price_{ 0, -4 };
};

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
