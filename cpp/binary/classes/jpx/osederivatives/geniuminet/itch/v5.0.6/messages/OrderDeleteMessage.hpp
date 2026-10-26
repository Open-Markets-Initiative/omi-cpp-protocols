#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

class Visitor;

// Sent whenever an order on the book is being deleted. There will be no remaining quantity.
class OrderDeleteMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderDeleteMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    OrderDeleteMessage() = default;
    OrderDeleteMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_id, std::uint32_t order_book_id, Side side);

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

    bool operator==(const OrderDeleteMessage& other) const;
    bool operator!=(const OrderDeleteMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint64_t order_id_{};
    std::uint32_t order_book_id_{};
    Side side_{};
};

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
