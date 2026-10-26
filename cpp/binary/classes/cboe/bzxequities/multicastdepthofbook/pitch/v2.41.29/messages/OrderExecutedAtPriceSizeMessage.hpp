#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/Message.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29 {

class Visitor;

// Order Executed at Price/Size messages are sent when a visible order on the Cboe book is
// executed in whole or in part at a different price than the limit price on the original Add
// Order message or the limit order price in the latest Modify Order message referencing the
// Order Id.
class OrderExecutedAtPriceSizeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderExecutedAtPriceSizeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 36;

    OrderExecutedAtPriceSizeMessage() = default;
    OrderExecutedAtPriceSizeMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, std::uint32_t executed_quantity, std::uint32_t remaining_quantity, std::uint64_t execution_id, Decimal price);

    // Time Offset: Nanosecond offset from last unit timestamp
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Order Id: Day-specific identifier assigned to this order
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Executed Quantity: Number of shares/contracts executed
    std::uint32_t executed_quantity() const;
    void set_executed_quantity(std::uint32_t value);

    // Remaining Quantity: Number of shares/contracts remaining after the execution
    std::uint32_t remaining_quantity() const;
    void set_remaining_quantity(std::uint32_t value);

    // Execution Id: Cboe generated day-unique execution identifier of this execution.
    // Execution Id is also referenced in the Trade Break message
    std::uint64_t execution_id() const;
    void set_execution_id(std::uint64_t value);

    // Price: The limit order price
    Decimal price() const;
    void set_price(Decimal value);

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

    bool operator==(const OrderExecutedAtPriceSizeMessage& other) const;
    bool operator!=(const OrderExecutedAtPriceSizeMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
    std::uint64_t order_id_{};
    std::uint32_t executed_quantity_{};
    std::uint32_t remaining_quantity_{};
    std::uint64_t execution_id_{};
    Decimal price_{ 0, -4 };
};

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29
