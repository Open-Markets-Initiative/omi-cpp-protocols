#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/Message.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

class Visitor;

// Relays information on state changes.
class OrderBookStateMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderBookStateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 28;

    OrderBookStateMessage() = default;
    OrderBookStateMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t order_book_id, const std::string& state_name);

    // Nanoseconds: Nanoseconds portion
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Order Book Id: Primary identifier of an order book
    std::uint32_t order_book_id() const;
    void set_order_book_id(std::uint32_t value);

    // State Name: Name of Order Book State
    const std::string& state_name() const;
    std::string& state_name();
    void set_state_name(const std::string& value);

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

    bool operator==(const OrderBookStateMessage& other) const;
    bool operator!=(const OrderBookStateMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t order_book_id_{};
    std::string state_name_{};
};

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
