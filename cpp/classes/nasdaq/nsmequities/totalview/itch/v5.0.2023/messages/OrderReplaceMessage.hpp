#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class Visitor;

// This message is sent whenever an order on the book has been cancel-replaced
class OrderReplaceMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderReplaceMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 34;

    OrderReplaceMessage() = default;
    OrderReplaceMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t original_order_reference_number, std::uint64_t new_order_reference_number, std::uint32_t shares, Decimal price);

    // Stock Locate: Locate Code uniquely assigned to the security symbol for the day
    std::uint16_t stock_locate() const;
    void set_stock_locate(std::uint16_t value);

    // Tracking Number: Nasdaq internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Original Order Reference Number: The original reference number of the order being
    // replaced
    std::uint64_t original_order_reference_number() const;
    void set_original_order_reference_number(std::uint64_t value);

    // New Order Reference Number: The new reference number for this order at time of
    // replacement
    std::uint64_t new_order_reference_number() const;
    void set_new_order_reference_number(std::uint64_t value);

    // Shares: The total number of shares associated with the order being added to the book
    std::uint32_t shares() const;
    void set_shares(std::uint32_t value);

    // Price: The display price of the new order
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
    std::uint16_t stock_locate_{};
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t original_order_reference_number_{};
    std::uint64_t new_order_reference_number_{};
    std::uint32_t shares_{};
    Decimal price_{ 0, -4 };
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
