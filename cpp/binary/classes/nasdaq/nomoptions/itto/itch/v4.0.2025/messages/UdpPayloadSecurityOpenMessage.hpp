#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../enums/OpenState.hpp"
#include "../messages/PacketMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class PacketMessageVisitor;

// NASDAQ plans to disseminate the Option Open Message for each option as soon as the opening
// is completed. Upon receipt of the open state message, firms should be advised that the
// option denoted in the message is now available for auto execution within the NASDAQ Options
// Market System. Upon receipt of the closed state message, firms should be advised that the
// option is no longer eligible for auto-execution within the NASDAQ Options Market System.
class UdpPayloadSecurityOpenMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::SecurityOpenMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 13;

    UdpPayloadSecurityOpenMessage() = default;
    UdpPayloadSecurityOpenMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint32_t option_id, OpenState open_state);

    // Tracking Number: Nasdaq Internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Option Id: Option ID assigned daily, valid for trading day.
    std::uint32_t option_id() const;
    void set_option_id(std::uint32_t value);

    // Open State: The allowable values are:
    OpenState open_state() const;
    void set_open_state(OpenState value);

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

    bool operator==(const UdpPayloadSecurityOpenMessage& other) const;
    bool operator!=(const UdpPayloadSecurityOpenMessage& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t option_id_{};
    OpenState open_state_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
