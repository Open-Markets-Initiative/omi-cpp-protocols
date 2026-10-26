#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../bitfields/OrderBookClearFlags.hpp"
#include "../messages/Message.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

class Visitor;

// Sent to instruct recipients to remove all orders from the order book for the specified
// instrument.
class OrderBookClearMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderBookClearMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 11;

    OrderBookClearMessage() = default;
    OrderBookClearMessage(std::uint32_t nanosecond, std::uint32_t instrument_id, const std::array<std::byte, 1>& reserved_a, const std::array<std::byte, 1>& reserved_b, const OrderBookClearFlags& order_book_clear_flags);

    // Nanosecond: Nanoseconds since last message, accurate to the nearest microsecond.
    std::uint32_t nanosecond() const;
    void set_nanosecond(std::uint32_t value);

    // Instrument Id: Instrument's symbol.
    std::uint32_t instrument_id() const;
    void set_instrument_id(std::uint32_t value);

    // Reserved A: Reserved field
    const std::array<std::byte, 1>& reserved_a() const;
    std::array<std::byte, 1>& reserved_a();
    void set_reserved_a(const std::array<std::byte, 1>& value);

    // Reserved B: Reserved field
    const std::array<std::byte, 1>& reserved_b() const;
    std::array<std::byte, 1>& reserved_b();
    void set_reserved_b(const std::array<std::byte, 1>& value);

    // Order Book Clear Flags: Order Book Clear Flags
    const OrderBookClearFlags& order_book_clear_flags() const;
    OrderBookClearFlags& order_book_clear_flags();
    void set_order_book_clear_flags(const OrderBookClearFlags& value);

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

    bool operator==(const OrderBookClearMessage& other) const;
    bool operator!=(const OrderBookClearMessage& other) const;

  private:
    std::uint32_t nanosecond_{};
    std::uint32_t instrument_id_{};
    std::array<std::byte, 1> reserved_a_{};
    std::array<std::byte, 1> reserved_b_{};
    OrderBookClearFlags order_book_clear_flags_{};
};

} // namespace lseg::millennium::level2::mitch::v11_9
