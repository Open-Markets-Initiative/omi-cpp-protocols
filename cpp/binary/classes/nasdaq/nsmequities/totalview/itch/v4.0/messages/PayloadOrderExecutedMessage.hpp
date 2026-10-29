#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/PacketMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

class PacketMessageVisitor;

// This message is sent whenever an order on the book is executed in whole or in part.
class PayloadOrderExecutedMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::OrderExecutedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 24;

    PayloadOrderExecutedMessage() = default;
    PayloadOrderExecutedMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_reference_number, std::uint32_t executed_shares, std::uint64_t match_number);

    // Nanoseconds: Nanoseconds portion of the timestamp.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Order Reference Number: The unique reference number assigned to the new order at the
    // time of receipt.
    std::uint64_t order_reference_number() const;
    void set_order_reference_number(std::uint64_t value);

    // Executed Shares: The number of shares executed.
    std::uint32_t executed_shares() const;
    void set_executed_shares(std::uint32_t value);

    // Match Number: The NASDAQ generated day-unique Match Number of this execution. The match
    // number is also referenced in the Trade Break Message.
    std::uint64_t match_number() const;
    void set_match_number(std::uint64_t value);

    // PacketMessage
    PacketMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(PacketMessageVisitor& visitor) const override;
    std::unique_ptr<PacketMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const PacketMessage& other) const override;

    bool operator==(const PayloadOrderExecutedMessage& other) const;
    bool operator!=(const PayloadOrderExecutedMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint64_t order_reference_number_{};
    std::uint32_t executed_shares_{};
    std::uint64_t match_number_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
