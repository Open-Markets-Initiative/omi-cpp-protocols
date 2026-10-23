#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../bitfields/AddAttributedOrderFlags.hpp"
#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

class Visitor;

// Indicates that a named order is added to the order book.
class AddAttributedOrderMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::AddAttributedOrderMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 43;

    AddAttributedOrderMessage() = default;
    AddAttributedOrderMessage(std::uint32_t nanosecond, std::uint64_t order_id, Side side, std::uint32_t quantity, std::uint32_t instrument_id, const std::array<std::byte, 1>& reserved_a, const std::array<std::byte, 1>& reserved_b, std::int64_t price, const std::string& attribution, const AddAttributedOrderFlags& add_attributed_order_flags);

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

    // Attribution: Identity of firm that submitted the order.
    const std::string& attribution() const;
    std::string& attribution();
    void set_attribution(const std::string& value);

    // Add Attributed Order Flags: Add Attributed Order Flags
    const AddAttributedOrderFlags& add_attributed_order_flags() const;
    AddAttributedOrderFlags& add_attributed_order_flags();
    void set_add_attributed_order_flags(const AddAttributedOrderFlags& value);

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

    bool operator==(const AddAttributedOrderMessage& other) const;
    bool operator!=(const AddAttributedOrderMessage& other) const;

  private:
    std::uint32_t nanosecond_{};
    std::uint64_t order_id_{};
    Side side_{};
    std::uint32_t quantity_{};
    std::uint32_t instrument_id_{};
    std::array<std::byte, 1> reserved_a_{};
    std::array<std::byte, 1> reserved_b_{};
    std::int64_t price_{};
    std::string attribution_{};
    AddAttributedOrderFlags add_attributed_order_flags_{};
};

} // namespace lseg::millennium::level2::mitch::v11_9
