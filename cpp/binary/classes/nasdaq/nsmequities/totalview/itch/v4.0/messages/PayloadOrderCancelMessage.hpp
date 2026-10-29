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

// This message is sent whenever an order on the book is modified as a result of a partial
// cancellation.
class PayloadOrderCancelMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::OrderCancelMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    PayloadOrderCancelMessage() = default;
    PayloadOrderCancelMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_reference_number, std::uint32_t canceled_shares);

    // Nanoseconds: Nanoseconds portion of the timestamp.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Order Reference Number: The unique reference number assigned to the new order at the
    // time of receipt.
    std::uint64_t order_reference_number() const;
    void set_order_reference_number(std::uint64_t value);

    // Canceled Shares: The number of shares being removed from the display size of the order
    // as the result of a cancellation.
    std::uint32_t canceled_shares() const;
    void set_canceled_shares(std::uint32_t value);

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

    bool operator==(const PayloadOrderCancelMessage& other) const;
    bool operator!=(const PayloadOrderCancelMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint64_t order_reference_number_{};
    std::uint32_t canceled_shares_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
