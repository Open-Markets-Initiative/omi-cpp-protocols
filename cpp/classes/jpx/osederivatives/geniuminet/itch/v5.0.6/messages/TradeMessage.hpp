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

// Execution details for normal match events involving non-displayable order types or cross
// trades.
class TradeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 49;

    TradeMessage() = default;
    TradeMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t match_id, std::uint32_t combo_group_id, Side side, std::uint64_t quantity, std::uint32_t order_book_id, std::int32_t trade_price, const std::string& owner_participant_id, const std::string& counterparty_participant_id, Printable printable, OccurredAtCross occurred_at_cross);

    // Nanoseconds: Nanoseconds portion
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Match Id: Assigned by the system to each match executed
    std::uint64_t match_id() const;
    void set_match_id(std::uint64_t value);

    // Combo Group Id: Used to group combination executions
    std::uint32_t combo_group_id() const;
    void set_combo_group_id(std::uint32_t value);

    // Side: B=Buy, S=Sell
    Side side() const;
    void set_side(Side value);

    // Quantity: Visible quantity
    std::uint64_t quantity() const;
    void set_quantity(std::uint64_t value);

    // Order Book Id: Primary identifier of an order book
    std::uint32_t order_book_id() const;
    void set_order_book_id(std::uint32_t value);

    // Trade Price: Execution price
    std::int32_t trade_price() const;
    void set_trade_price(std::int32_t value);

    // Owner Participant Id: Owner ID (blank for anonymous markets)
    const std::string& owner_participant_id() const;
    std::string& owner_participant_id();
    void set_owner_participant_id(const std::string& value);

    // Counterparty Participant Id: Counterparty ID (blank for anonymous markets)
    const std::string& counterparty_participant_id() const;
    std::string& counterparty_participant_id();
    void set_counterparty_participant_id(const std::string& value);

    // Printable: Y=Printable, N=Non-printable
    Printable printable() const;
    void set_printable(Printable value);

    // Occurred At Cross: Y=Yes, N=No
    OccurredAtCross occurred_at_cross() const;
    void set_occurred_at_cross(OccurredAtCross value);

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

    bool operator==(const TradeMessage& other) const;
    bool operator!=(const TradeMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint64_t match_id_{};
    std::uint32_t combo_group_id_{};
    Side side_{};
    std::uint64_t quantity_{};
    std::uint32_t order_book_id_{};
    std::int32_t trade_price_{};
    std::string owner_participant_id_{};
    std::string counterparty_participant_id_{};
    Printable printable_{};
    OccurredAtCross occurred_at_cross_{};
};

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
