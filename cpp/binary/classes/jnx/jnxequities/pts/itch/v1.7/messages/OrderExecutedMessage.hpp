#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/SequencedMessage.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

class SequencedMessageVisitor;

// Order Executed Message is sent whenever an order in the book is executed in whole or part.
class OrderExecutedMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::OrderExecutedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 24;

    OrderExecutedMessage() = default;
    OrderExecutedMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_number, std::uint32_t executed_quantity, std::uint64_t match_number);

    // Nanoseconds: Number of nanoseconds since last Timestamp Seconds Message.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Order Number: Reference number of the accepted order; zero indicates a reference price
    // message.
    std::uint64_t order_number() const;
    void set_order_number(std::uint64_t value);

    // Executed Quantity: Number of shares executed.
    std::uint32_t executed_quantity() const;
    void set_executed_quantity(std::uint32_t value);

    // Match Number: Reference number of the match.
    std::uint64_t match_number() const;
    void set_match_number(std::uint64_t value);

    // SequencedMessage
    SequencedMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(SequencedMessageVisitor& visitor) const override;
    std::unique_ptr<SequencedMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const SequencedMessage& other) const override;

    bool operator==(const OrderExecutedMessage& other) const;
    bool operator!=(const OrderExecutedMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint64_t order_number_{};
    std::uint32_t executed_quantity_{};
    std::uint64_t match_number_{};
};

} // namespace jnx::jnxequities::pts::itch::v1_7
