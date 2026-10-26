#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../bitfields/OrderAttributes.hpp"
#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

class Visitor;

// Sent whenever an existing order on the book has been modified. Note: Specification says this
// message is not used, but remains for future reference.
class OrderReplaceMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderReplaceMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 35;

    OrderReplaceMessage() = default;
    OrderReplaceMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_id, std::uint32_t order_book_id, Side side, std::uint32_t new_orderbook_position, std::uint64_t quantity, std::int32_t price, const OrderAttributes& order_attributes);

    // Nanoseconds: Nanoseconds portion
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Order Id: Identifier assigned to the new order
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Order Book Id: Primary identifier of an order book
    std::uint32_t order_book_id() const;
    void set_order_book_id(std::uint32_t value);

    // Side: B=Buy, S=Sell
    Side side() const;
    void set_side(Side value);

    // New Orderbook Position: New rank within orderbook
    std::uint32_t new_orderbook_position() const;
    void set_new_orderbook_position(std::uint32_t value);

    // Quantity: Visible quantity
    std::uint64_t quantity() const;
    void set_quantity(std::uint64_t value);

    // Price: Display price
    std::int32_t price() const;
    void set_price(std::int32_t value);

    // Order Attributes: Additional order attributes
    const OrderAttributes& order_attributes() const;
    OrderAttributes& order_attributes();
    void set_order_attributes(const OrderAttributes& value);

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
    std::chrono::nanoseconds nanoseconds_{};
    std::uint64_t order_id_{};
    std::uint32_t order_book_id_{};
    Side side_{};
    std::uint32_t new_orderbook_position_{};
    std::uint64_t quantity_{};
    std::int32_t price_{};
    OrderAttributes order_attributes_{};
};

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
