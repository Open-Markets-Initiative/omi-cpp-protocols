#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../bitfields/OrderModifiedFlags.hpp"
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
    OrderModifiedMessage(std::uint32_t nanosecond, std::uint64_t order_id, std::uint32_t new_quantity, std::int64_t new_price, const OrderModifiedFlags& order_modified_flags);

    // Nanosecond: Nanoseconds since last message, accurate to the nearest microsecond.
    std::uint32_t nanosecond() const;
    void set_nanosecond(std::uint32_t value);

    // Order Id: Unique identifier of the order.
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // New Quantity: New displayed quantity of the order.
    std::uint32_t new_quantity() const;
    void set_new_quantity(std::uint32_t value);

    // New Price: New limit price of the order.
    std::int64_t new_price() const;
    void set_new_price(std::int64_t value);

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
    std::uint32_t nanosecond_{};
    std::uint64_t order_id_{};
    std::uint32_t new_quantity_{};
    std::int64_t new_price_{};
    OrderModifiedFlags order_modified_flags_{};
};

} // namespace lseg::millennium::level2::mitch::v11_9
