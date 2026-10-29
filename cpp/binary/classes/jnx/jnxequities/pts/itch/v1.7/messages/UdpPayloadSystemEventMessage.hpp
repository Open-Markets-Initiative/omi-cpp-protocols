#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/Group.hpp"
#include "../enums/SystemEvent.hpp"
#include "../messages/PacketMessage.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

class PacketMessageVisitor;

// System Event Messages signal data feed, system and market events.
class UdpPayloadSystemEventMessage : public PacketMessage {
  public:
    // The code that selects this message
    static constexpr PacketMessageCode message_type = MessageType::SystemEventMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 9;

    UdpPayloadSystemEventMessage() = default;
    UdpPayloadSystemEventMessage(std::chrono::nanoseconds nanoseconds, const std::string& group, SystemEvent system_event);

    // Nanoseconds: Number of nanoseconds since last Timestamp Seconds Message.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Group: Orderbook group identifier.
    const std::string& group() const;
    std::string& group();
    void set_group(const std::string& value);

    // System Event: Refer to the System Events table below.
    SystemEvent system_event() const;
    void set_system_event(SystemEvent value);

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
    std::chrono::nanoseconds nanoseconds_{};
    std::string group_{};
    SystemEvent system_event_{};
};

} // namespace jnx::jnxequities::pts::itch::v1_7
