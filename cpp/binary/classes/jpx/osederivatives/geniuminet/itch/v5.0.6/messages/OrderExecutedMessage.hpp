#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/Side.hpp"
#include "../messages/Message.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

class Visitor;

// Sent whenever an order on the book is executed in whole or in part.
class OrderExecutedMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OrderExecutedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 51;

    OrderExecutedMessage() = default;
    OrderExecutedMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_id, std::uint32_t order_book_id, Side side, std::uint64_t executed_quantity, std::uint64_t match_id, std::uint32_t combo_group_id, const std::string& participant_id_owner, const std::string& participant_id_counterparty);

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

    // Participant Id Owner: Owner ID (blank for anonymous markets)
    const std::string& participant_id_owner() const;
    std::string& participant_id_owner();
    void set_participant_id_owner(const std::string& value);

    // Participant Id Counterparty: Counterparty ID (blank for anonymous markets)
    const std::string& participant_id_counterparty() const;
    std::string& participant_id_counterparty();
    void set_participant_id_counterparty(const std::string& value);

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

    bool operator==(const OrderExecutedMessage& other) const;
    bool operator!=(const OrderExecutedMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint64_t order_id_{};
    std::uint32_t order_book_id_{};
    Side side_{};
    std::uint64_t executed_quantity_{};
    std::uint64_t match_id_{};
    std::uint32_t combo_group_id_{};
    std::string participant_id_owner_{};
    std::string participant_id_counterparty_{};
};

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
