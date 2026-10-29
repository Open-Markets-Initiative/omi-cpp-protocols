#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../messages/PacketMessage.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

class PacketMessageVisitor;

// Order Replaced Message is sent whenever an order in the book has been replaced.
class UdpPayloadOrderReplacedMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::OrderReplacedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 28;

    UdpPayloadOrderReplacedMessage() = default;
    UdpPayloadOrderReplacedMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t original_order_number, std::uint64_t new_order_number, std::uint32_t quantity, Decimal price);

    // Nanoseconds: Number of nanoseconds since last Timestamp Seconds Message.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Original Order Number: Reference number of the original order.
    std::uint64_t original_order_number() const;
    void set_original_order_number(std::uint64_t value);

    // New Order Number: Reference number of the replaced order.
    std::uint64_t new_order_number() const;
    void set_new_order_number(std::uint64_t value);

    // Quantity: Total number of shares added to the book.
    std::uint32_t quantity() const;
    void set_quantity(std::uint32_t value);

    // Price: Price of the order; for a reference price message, a value of 214,748,364.7
    // (7FFFFFFF hex) denotes no reference price available.
    Decimal price() const;
    void set_price(Decimal value);

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

    bool operator==(const UdpPayloadOrderReplacedMessage& other) const;
    bool operator!=(const UdpPayloadOrderReplacedMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint64_t original_order_number_{};
    std::uint64_t new_order_number_{};
    std::uint32_t quantity_{};
    Decimal price_{ 0, -1 };
};

} // namespace jnx::jnxequities::pts::itch::v1_7
