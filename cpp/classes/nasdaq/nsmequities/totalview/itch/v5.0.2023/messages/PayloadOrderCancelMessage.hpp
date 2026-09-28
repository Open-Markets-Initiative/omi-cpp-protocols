#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/PacketMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class PacketMessageVisitor;

// This message is sent whenever an order on the book is modified as a result of a partial
// cancellation
class PayloadOrderCancelMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::OrderCancelMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 22;

    PayloadOrderCancelMessage() = default;
    PayloadOrderCancelMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t order_reference_number, std::uint32_t canceled_shares);

    // Stock Locate: Locate Code uniquely assigned to the security symbol for the day
    std::uint16_t stock_locate() const;
    void set_stock_locate(std::uint16_t value);

    // Tracking Number: Nasdaq internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Order Reference Number: The unique reference number assigned to the new order at the
    // time of receipt
    std::uint64_t order_reference_number() const;
    void set_order_reference_number(std::uint64_t value);

    // Canceled Shares: The number of shares being removed from the display size of the order
    // as the result of a cancellation
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
    std::uint16_t stock_locate_{};
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t order_reference_number_{};
    std::uint32_t canceled_shares_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
