#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/PacketMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class PacketMessageVisitor;

// The message is sent when an order or a side of a quote is being cancelled. All remaining
// contracts are no longer accessible so the side should be removed from the book.
class UdpPayloadSingleSideDeleteMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::SingleSideDeleteMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    UdpPayloadSingleSideDeleteMessage() = default;
    UdpPayloadSingleSideDeleteMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t reference_number);

    // Tracking Number: Nasdaq Internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Reference Number: The order/quote reference number associated with the executed order.
    std::uint64_t reference_number() const;
    void set_reference_number(std::uint64_t value);

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

    bool operator==(const UdpPayloadSingleSideDeleteMessage& other) const;
    bool operator!=(const UdpPayloadSingleSideDeleteMessage& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t reference_number_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
