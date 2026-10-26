#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/Printable.hpp"
#include "../messages/Message.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

class Visitor;

// Sent if a displayed order is fully or partially filled at a price that is different from its
// displayed price.
class OrderExecutedWithPriceSizeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderExecutedWithPriceSizeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 37;

    OrderExecutedWithPriceSizeMessage() = default;
    OrderExecutedWithPriceSizeMessage(std::uint32_t nanosecond, std::uint64_t order_id, std::uint32_t executed_quantity, std::uint32_t display_quantity, std::uint64_t trade_match_id, Printable printable, std::int64_t price);

    // Nanosecond: Nanoseconds since last message, accurate to the nearest microsecond.
    std::uint32_t nanosecond() const;
    void set_nanosecond(std::uint32_t value);

    // Order Id: Unique identifier of the order.
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Executed Quantity: Quantity executed.
    std::uint32_t executed_quantity() const;
    void set_executed_quantity(std::uint32_t value);

    // Display Quantity: Displayed quantity of the order after the execution.
    std::uint32_t display_quantity() const;
    void set_display_quantity(std::uint32_t value);

    // Trade Match Id: Unique identifier of the trade.
    std::uint64_t trade_match_id() const;
    void set_trade_match_id(std::uint64_t value);

    // Printable: Printable
    Printable printable() const;
    void set_printable(Printable value);

    // Price: Limit price of the order.
    std::int64_t price() const;
    void set_price(std::int64_t value);

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

    bool operator==(const OrderExecutedWithPriceSizeMessage& other) const;
    bool operator!=(const OrderExecutedWithPriceSizeMessage& other) const;

  private:
    std::uint32_t nanosecond_{};
    std::uint64_t order_id_{};
    std::uint32_t executed_quantity_{};
    std::uint32_t display_quantity_{};
    std::uint64_t trade_match_id_{};
    Printable printable_{};
    std::int64_t price_{};
};

} // namespace lseg::millennium::level2::mitch::v11_9
