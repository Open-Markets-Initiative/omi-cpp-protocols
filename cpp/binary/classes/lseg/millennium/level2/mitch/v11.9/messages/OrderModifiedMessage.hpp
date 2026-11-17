// Lseg.Millennium.Level2.Mitch.v11.9: messages/OrderModifiedMessage.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../bitfields/OrderModifiedFlags.hpp"
#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

class Visitor;

// Indicates that the displayed quantity or price of a displayed order has been updated.
class OrderModifiedMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderModifiedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 25;

    OrderModifiedMessage() = default;
    OrderModifiedMessage(std::chrono::nanoseconds nanosecond, std::uint64_t order_id, std::uint32_t new_quantity, Decimal new_price, const OrderModifiedFlags& order_modified_flags);

    // Nanosecond: Nanoseconds since last message, accurate to the nearest microsecond.
    std::chrono::nanoseconds nanosecond() const;
    void set_nanosecond(std::chrono::nanoseconds value);

    // Order Id: Unique identifier of the order.
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // New Quantity: New displayed quantity of the order.
    std::uint32_t new_quantity() const;
    void set_new_quantity(std::uint32_t value);

    // New Price: New limit price of the order.
    Decimal new_price() const;
    void set_new_price(Decimal value);

    // Order Modified Flags: Order Modified Flags
    const OrderModifiedFlags& order_modified_flags() const;
    OrderModifiedFlags& order_modified_flags();
    void set_order_modified_flags(const OrderModifiedFlags& value);

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

    bool operator==(const OrderModifiedMessage& other) const;
    bool operator!=(const OrderModifiedMessage& other) const;

  private:
    std::chrono::nanoseconds nanosecond_{};
    std::uint64_t order_id_{};
    std::uint32_t new_quantity_{};
    Decimal new_price_{ 0, -8 };
    OrderModifiedFlags order_modified_flags_{};
};

} // namespace lseg::millennium::level2::mitch::v11_9
