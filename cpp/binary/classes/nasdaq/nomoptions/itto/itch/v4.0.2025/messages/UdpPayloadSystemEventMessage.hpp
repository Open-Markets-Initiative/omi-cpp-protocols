#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../enums/EventCode.hpp"
#include "../messages/PacketMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class PacketMessageVisitor;

// The system event message type is used to signal a market or data feed handler event.
class UdpPayloadSystemEventMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::SystemEventMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 9;

    UdpPayloadSystemEventMessage() = default;
    UdpPayloadSystemEventMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, EventCode event_code);

    // Tracking Number: Nasdaq Internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Event Code: Refer to System Event Codes below
    EventCode event_code() const;
    void set_event_code(EventCode value);

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

    bool operator==(const UdpPayloadSystemEventMessage& other) const;
    bool operator!=(const UdpPayloadSystemEventMessage& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    EventCode event_code_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
