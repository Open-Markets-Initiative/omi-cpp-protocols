#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../bitfields/AddOrderFlags.hpp"
#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

class Visitor;

// Sent to indicate that an anonymous limit or market order is added to the order book.
class AddOrderMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AddOrderMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 42;

    AddOrderMessage() = default;
    AddOrderMessage(std::uint32_t nanosecond, std::uint64_t order_id, Side side, std::uint32_t quantity, std::uint32_t instrument_id, const std::array<std::byte, 1>& reserved_a, const std::array<std::byte, 1>& reserved_b, std::int64_t price, const AddOrderFlags& add_order_flags, const std::array<std::byte, 10>& reserved_10);

    // Nanosecond: Nanoseconds since last message, accurate to the nearest microsecond.
    std::uint32_t nanosecond() const;
    void set_nanosecond(std::uint32_t value);

    // Order Id: Unique identifier of the order.
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Side: Side
    Side side() const;
    void set_side(Side value);

    // Quantity: Displayed quantity of the order.
    std::uint32_t quantity() const;
    void set_quantity(std::uint32_t value);

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

    // Price: Limit price of the order.
    std::int64_t price() const;
    void set_price(std::int64_t value);

    // Add Order Flags: Add Order Flags
    const AddOrderFlags& add_order_flags() const;
    AddOrderFlags& add_order_flags();
    void set_add_order_flags(const AddOrderFlags& value);

    // Reserved 10: Reserved field
    const std::array<std::byte, 10>& reserved_10() const;
    std::array<std::byte, 10>& reserved_10();
    void set_reserved_10(const std::array<std::byte, 10>& value);

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

    bool operator==(const AddOrderMessage& other) const;
    bool operator!=(const AddOrderMessage& other) const;

  private:
    std::uint32_t nanosecond_{};
    std::uint64_t order_id_{};
    Side side_{};
    std::uint32_t quantity_{};
    std::uint32_t instrument_id_{};
    std::array<std::byte, 1> reserved_a_{};
    std::array<std::byte, 1> reserved_b_{};
    std::int64_t price_{};
    AddOrderFlags add_order_flags_{};
    std::array<std::byte, 10> reserved_10_{};
};

} // namespace lseg::millennium::level2::mitch::v11_9
