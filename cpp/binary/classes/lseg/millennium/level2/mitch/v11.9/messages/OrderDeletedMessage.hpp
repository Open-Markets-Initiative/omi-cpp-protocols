#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../bitfields/OrderDeletedFlags.hpp"
#include "../messages/Message.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

class Visitor;

// Sent to indicate that the remainder of a displayed order is cancelled.
class OrderDeletedMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderDeletedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    OrderDeletedMessage() = default;
    OrderDeletedMessage(std::uint32_t nanosecond, std::uint64_t order_id, const OrderDeletedFlags& order_deleted_flags, std::uint32_t instrument_id);

    // Nanosecond: Nanoseconds since last message, accurate to the nearest microsecond.
    std::uint32_t nanosecond() const;
    void set_nanosecond(std::uint32_t value);

    // Order Id: Unique identifier of the order.
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Order Deleted Flags: Order Deleted Flags
    const OrderDeletedFlags& order_deleted_flags() const;
    OrderDeletedFlags& order_deleted_flags();
    void set_order_deleted_flags(const OrderDeletedFlags& value);

    // Instrument Id: Instrument's symbol.
    std::uint32_t instrument_id() const;
    void set_instrument_id(std::uint32_t value);

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

    bool operator==(const OrderDeletedMessage& other) const;
    bool operator!=(const OrderDeletedMessage& other) const;

  private:
    std::uint32_t nanosecond_{};
    std::uint64_t order_id_{};
    OrderDeletedFlags order_deleted_flags_{};
    std::uint32_t instrument_id_{};
};

} // namespace lseg::millennium::level2::mitch::v11_9
