#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/OccurredAtCross.hpp"
#include "../enums/Printable.hpp"
#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

class Visitor;

// Sent when an order is executed at a price different than the initial display price.
class OrderExecutedWithPriceMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderExecutedWithPriceMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 57;

    OrderExecutedWithPriceMessage() = default;
    OrderExecutedWithPriceMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_id, std::uint32_t order_book_id, Side side, std::uint64_t executed_quantity, std::uint64_t match_id, std::uint32_t combo_group_id, const std::string& owner_participant_id, const std::string& counterparty_participant_id, std::int32_t trade_price, OccurredAtCross occurred_at_cross, Printable printable);

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

    // Executed Quantity: The quantity being executed
    std::uint64_t executed_quantity() const;
    void set_executed_quantity(std::uint64_t value);

    // Match Id: Assigned by the system to each match executed
    std::uint64_t match_id() const;
    void set_match_id(std::uint64_t value);

    // Combo Group Id: Used to group combination executions
    std::uint32_t combo_group_id() const;
    void set_combo_group_id(std::uint32_t value);

    // Owner Participant Id: Owner ID (blank for anonymous markets)
    const std::string& owner_participant_id() const;
    std::string& owner_participant_id();
    void set_owner_participant_id(const std::string& value);

    // Counterparty Participant Id: Counterparty ID (blank for anonymous markets)
    const std::string& counterparty_participant_id() const;
    std::string& counterparty_participant_id();
    void set_counterparty_participant_id(const std::string& value);

    // Trade Price: Execution price
    std::int32_t trade_price() const;
    void set_trade_price(std::int32_t value);

    // Occurred At Cross: Y=Yes, N=No
    OccurredAtCross occurred_at_cross() const;
    void set_occurred_at_cross(OccurredAtCross value);

    // Printable: Y=Printable, N=Non-printable
    Printable printable() const;
    void set_printable(Printable value);

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

    bool operator==(const OrderExecutedWithPriceMessage& other) const;
    bool operator!=(const OrderExecutedWithPriceMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint64_t order_id_{};
    std::uint32_t order_book_id_{};
    Side side_{};
    std::uint64_t executed_quantity_{};
    std::uint64_t match_id_{};
    std::uint32_t combo_group_id_{};
    std::string owner_participant_id_{};
    std::string counterparty_participant_id_{};
    std::int32_t trade_price_{};
    OccurredAtCross occurred_at_cross_{};
    Printable printable_{};
};

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
